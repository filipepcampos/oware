#include <iostream>
#include <cstdlib>
#include <cstring>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "../include/Tcp.h"
#include "../include/Text.h"


namespace Tcp{
    struct GameInformation{
        const int ID;
        Player &player;
        std::string opponent_name;
        Board &board;
        int sock;
    };

    void playGame(){
        WSADATA wsaData;
        WSAStartup(MAKEWORD(1, 1), &wsaData);
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in server;
        inet_pton(AF_INET, ip_address.c_str(), &server.sin_addr);
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);

        std::string ip_address = readIpAddress();
        if(ip_address.empty()){
            // If no address is specified, try to connect to localhost so there's only 1 host per computer
            ip_address = "127.0.0.1";
            inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);
            if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
                host();
                return;
            }
            std::cout << TEXT_ALREADY_HOST << std::endl;
            client(sock);
            return;
        }
        // Try to connect to given ip address. If connection is not possible, host the game
        inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);
        if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
            std::cout << TEXT_SERVER_NOT_FOUND << std::endl;
            host();
            return;
        }
        client(sock);
    }

    std::string readIpAddress(){
        std::cout << std::endl << TEXT_IP_ADDRESS_PROMPT << std::endl;
        std::string ip_address;
        std::cout << "> "; std::getline(std::cin, ip_address);
        if(std::cin.eof()){
            std::cin.clear();
        }
        return ip_address;
    }

    void client(int sock){
        char buffer[1] = {0};
        read(sock, buffer, 1);
        if(buffer[0] == 0){
            std::cout << TEXT_ONGOING_GAME << std::endl;
            exit(1);
        }
        const int ID = 1;
        Player player(ID);

        const char* name_str = player.name.c_str();
        send(sock , name_str, strlen(name_str) , 0);
        std::string opponent_name = readOpponentName(sock);

        Board board;
        board.registerPlayerNames(opponent_name, player.name);
        GameInformation info = {ID, player, opponent_name, board, sock};
        play(info);
    }

    void host(){
        const int ID = 0;
        printHostIP();
        int client_socket = initializeServer();
        Player player(ID);

        std::string opponent_name = readOpponentName(client_socket);
        const char* name_str = player.name.c_str();
        send(client_socket, name_str, strlen(name_str), 0);

        Board board;
        board.registerPlayerNames(player.name, opponent_name);
        GameInformation info = {ID, player, opponent_name, board, client_socket};
        play(info);
    }

    std::string readOpponentName(int sock){
        char buffer[1024] = {0};
        recv(sock, buffer, 1024, 0);
        if(buffer[0] == 0){
            std::cout << TEXT_FAILED_GET_OPPONENT_INFO << std::endl;
            exit(1);
        }
        std::string result = buffer;
        return result;
    }

    void play(GameInformation &game){
        int turn = 1;
        char buffer[1];
        int opponent_id = 1 - game.ID;
        do{
            turn = (turn+1) % 2;
            if(turn == game.ID){
                char move = game.player.play(game.board);
                char information[1] = {move};
                send(game.sock, information, 1, 0);
            }
            else{
                std::cout << COLOR[opponent_id] << game.opponent_name << TEXT_TURN << RESET << std::endl;
                buffer[0] = 0;
                recv(game.sock, buffer, 1, 0);
                char move = buffer[0];
                if(move == 'x'){
                    game.board.forceEnd();
                    continue;
                }
                if(move == 0){
                    std::cout << TEXT_OPPONENT_DISCONNECTED << std::endl;
                    game.board.terminate();
                    continue;
                }
                game.board.play(move, opponent_id);
            }
        } while(!game.board.gameOver(turn));
        closesocket(game.sock);
        WSACleanup();
    }

    int initializeServer(){
        SOCKET server_socket, new_socket;
        struct sockaddr_in server, client;
        int c;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(PORT);
        bind(server_socket, (struct sockaddr *)&server, sizeof(server));
        listen(server_socket, 3);
        c = sizeof(struct sockaddr_in);
        std::cout << TEXT_SERVER_INITIALIZED << std::endl;
        new_socket = accept(server_socket, (struct sockaddr *)&client, &c);
        std::cout << TEXT_CONNECTION_ESTABLISHED << std::endl;
        char confirmation[1] = {1};
        send(new_socket, confirmation, 1, 0);
        return new_socket;
    }

    void printHostIP(){
        const char* google_dns_server = "8.8.8.8";
        int dns_port = 53;
        struct sockaddr_in server;
        SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
        server.sin_family = AF_INET;
        inet_pton(AF_INET, google_dns_server, &server.sin_addr);
        server.sin_port = htons(dns_port);
        connect(sock, (const struct sockaddr*)&server, sizeof(server));
        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        getsockname(sock, (struct sockaddr*)&name, &namelen);
        char buffer[80];
        const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
        if(p != nullptr)
        {
            std::cout << TEXT_LOCAL_IP << buffer << std::endl;
        }
        closesocket(sock);
    }
}