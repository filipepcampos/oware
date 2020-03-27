#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include "../include/Tcp.h"

Tcp::Tcp(){
    int sock = 0;
    struct sockaddr_in server_address;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
    if(connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        std::cout << "[+] host\n";
        host();
        return;
    }
    client(sock);
}

void Tcp::client(int sock){
    const int ID = 1;
    Player player(ID);
    Board board;
    std::cout << "[-] client\n";
    const char* name_str = player.name.c_str();
    send(sock , name_str, strlen(name_str) , 0);
    std::cout << "[-] name sent\n";
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    opponent_name = buffer;
    std::cout << opponent_name << std::endl;
    board.registerPlayerNames(opponent_name, player.name);
    play(ID, player, board, sock);
}

void Tcp::host(){
    const int ID = 0;
    int client_socket = initializeServer();
    Player player(ID);
    Board board;
    char buffer[1024] = {0};

    read(client_socket, buffer, 1024);
    opponent_name = buffer;
    std::cout << opponent_name << std::endl;

    const char* name_str = player.name.c_str();
    send(client_socket, name_str, strlen(name_str), 0);
    std::cout << "[+] name sent\n";

    board.registerPlayerNames(player.name, opponent_name);
    play(ID, player, board, client_socket);
}

void Tcp::play(const int ID, Player &player, Board &board, int sock){
    int turn = 1;
    char buffer[1024];
    do{
        turn = (turn+1) % 2;
        if(turn == ID){
            char move = player.play(board);
            char information[1] = {move};
            send(sock, information, 1, 0);
        }
        else{
            read(sock, buffer, 1024);
            char move = buffer[0];
            if(move == 'x'){
                board.forceEnd();
                continue;
            }
            board.play(move, 1 - ID);
        }
    } while(!board.gameOver(turn));
}

int Tcp::initializeServer(){
    int server_socket, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int address_len = sizeof(address);

    // Creating socket file descriptor
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "[!] socket failed";
        exit(EXIT_FAILURE);
    }
    std::cout << "[+] socket created\n";

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        std::cerr << "[!] set sock opt\n";
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    std::cout << "[+] socket attached\n";

    // Forcefully attaching socket to the port 8080
    if (bind(server_socket, (struct sockaddr *)&address,
             sizeof(address))<0)
    {
        std::cerr << "[!] bind failed\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "[+] bind successful\n";
    if (listen(server_socket, 3) < 0)
    {
        std::cerr << "[!] listen failed";
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_socket, (struct sockaddr *)&address,
                             (socklen_t*)&address_len)) < 0)
    {
        std::cerr << "[!] accept";
        exit(EXIT_FAILURE);
    }
    return new_socket;
}