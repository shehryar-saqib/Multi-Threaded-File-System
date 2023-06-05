#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "util.cpp"

#define PORT 8080

using namespace std;

int main(int argument, char const *argv[])
{
    int obj_socket = 0, reader;
    struct sockaddr_in serv_addr;
    string address = argv[1];
    
    if ((obj_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error !");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(address.c_str());
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address ! This IP Address is not supported !\n");
        return -1;
    }
    if (connect(obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed : Can't establish a connection over this socket !");
        return -1;
    }
    while(true)
    {
        char *message = new char;
        char buffer[2048] = {0};

        printf("Enter the Command: ");
        cin.getline(message, 2048);
        send(obj_socket, message, strlen(message), 0);
        vector<string> commands = string_splitter(message, ' ');

        if(strcmp(message, "close") == 0){
            break;
        }
        reader = read(obj_socket, buffer, 2048);
        printf("%s\n", buffer);
    }
    
    return 0;
}