#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
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
        int sock = 0;
        struct sockaddr_in server_address;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);

        std::string ip_address = readIpAddress();
        if(ip_address.empty()){
            // If no address is specified, try to connect to localhost so there's only 1 host per computer
            ip_address = "127.0.0.1";
            inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);
            if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
                host();
                return;
            }
            std::cout << TEXT.at("ALREADY_HOST") << std::endl;
            client(sock);
            return;
        }
        // Try to connect to given ip address. If connection is not possible, host the game
        int status = inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);
        if(status < 1 || connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
            std::cout << TEXT.at("SERVER_NOT_FOUND") << std::endl;
            host();
            return;
        }
        client(sock);
    }

     std::string readIpAddress(){
         std::cout << std::endl << TEXT.at("IP_ADDRESS_PROMPT") << std::endl;
         std::string ip_address;
         std::cout << "> "; std::getline(std::cin, ip_address);
         if(std::cin.eof()){
             std::cout << TEXT.at("IOERROR") << std::endl;
             exit(1);
         }
         return ip_address;
     }

    void client(int sock){
        char buffer[1];
        read(sock, buffer, 1);
        if(buffer[0] == 0){
            std::cout << TEXT.at("ONGOING_GAME") << std::endl;
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
        read(sock, buffer, 1024);
        if(buffer[0] == 0){
            std::cout << TEXT.at("FAILED_GET_OPPONENT_INFO") << std::endl;
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
                std::cout << COLOR[opponent_id] << game.opponent_name << TEXT.at("TURN") << RESET << std::endl;
                buffer[0] = 0;
                read(game.sock, buffer, 1);
                char move = buffer[0];
                switch(move){
                    case 'x': game.board.forceEnd(); break;
                    case 0: std::cout << TEXT.at("OPPONENT_DISCONNECTED") << std::endl;  game.board.terminate(); break;
                    default: game.board.play(move, opponent_id);
                }
            }
        } while(!game.board.gameOver(turn));
        close(game.sock);
    }

    int initializeServer(){
        int server_socket, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int address_len = sizeof(address);

        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        bind(server_socket, (struct sockaddr *)&address, sizeof(address));
        listen(server_socket, 3);
        std::cout << TEXT.at("SERVER_INITIALIZED") << std::endl;

        new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&address_len);
        char confirmation[1] = {1};
        send(new_socket, confirmation, 1, 0);
        std::cout << TEXT.at("CONNECTION_ESTABLISHED") << std::endl;
        return new_socket;
    }

    void printHostIP(){
        const char* google_dns_server = "8.8.8.8";
        int dns_port = 53;
        struct sockaddr_in server;
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(google_dns_server);
        server.sin_port = htons(dns_port);
        connect(sock, (const struct sockaddr*)&server, sizeof(server));

        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        getsockname(sock, (struct sockaddr*)&name, &namelen);
        char buffer[80];
        const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
        if(p != nullptr)
        {
            std::cout << TEXT.at("LOCAL_IP") << buffer << std::endl;
        }
        close(sock);
    }

}