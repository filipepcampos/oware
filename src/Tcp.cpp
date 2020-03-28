#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../include/Tcp.h"


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
        std::cout << "If you wish to join a game, type the id adress. To host please press enter" << std::endl;
        std::string ip_address;
        std::cout << "> "; std::getline(std::cin, ip_address);
        if(ip_address.empty()){
            host();
            return;
        }
        else{
            inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);
            if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
                std::cout << "No server found at given ip address." << std::endl;
                host();
                return;
            }
            client(sock);
        }
    }

    void client(int sock){
        const int ID = 1;
        Player player(ID);

        const char* name_str = player.name.c_str();
        send(sock , name_str, strlen(name_str) , 0);

        char buffer[1024] = {0};
        read(sock, buffer, 1024);
        if(buffer[0] == 0){
            std::cout << "Couldn't get opponent information" << std::endl;
            exit(1);
        }
        std::string opponent_name = buffer;

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

        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        if(buffer[0] == 0){
            std::cout << "Couldn't get opponent information" << std::endl;
            exit(1);
        }
        std::string opponent_name = buffer;

        const char* name_str = player.name.c_str();
        send(client_socket, name_str, strlen(name_str), 0);

        Board board;
        board.registerPlayerNames(player.name, opponent_name);
        GameInformation info = {ID, player, opponent_name, board, client_socket};
        play(info);
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
                std::cout << COLOR[opponent_id] << game.opponent_name << "'s turn." << RESET << std::endl;
                buffer[0] = 'z';
                read(game.sock, buffer, 1);
                char move = buffer[0];
                if(move == 'x'){
                    game.board.forceEnd();
                    continue;
                }
                if(move == 'z'){
                    std::cout << "Opponent has disconnected.";
                    game.board.terminate();
                    continue;
                }
                game.board.play(move, opponent_id);
            }
        } while(!game.board.gameOver(turn));
    }

    int initializeServer(){
        int server_socket, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int address_len = sizeof(address);

        if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            std::cerr << "[!] socket failed";
            exit(1);
        }

        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        {
            std::cerr << "[!] set sock opt\n";
            exit(1);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        if (bind(server_socket, (struct sockaddr *)&address, sizeof(address))<0)
        {
            std::cerr << "[!] bind failed\n";
            exit(1);
        }
        if (listen(server_socket, 3) < 0)
        {
            std::cerr << "[!] listen failed";
            exit(1);
        }
        std::cout << "Server listening." << std::endl;
        if ((new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&address_len)) < 0)
        {
            std::cerr << "[!] accept";
            exit(1);
        }
        std::cout << "Connection established." << std::endl;
        return new_socket;
    }

    void printHostIP(){
        const char* google_dns_server = "8.8.8.8";
        int dns_port = 53;
        struct sockaddr_in serv;
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(google_dns_server);
        serv.sin_port = htons(dns_port);
        connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        getsockname(sock, (struct sockaddr*)&name, &namelen);
        char buffer[80];
        const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 80);
        if(p != nullptr)
        {
            std::cout << "Local IP address is: " << buffer << std::endl;
        }
        close(sock);
    }

}