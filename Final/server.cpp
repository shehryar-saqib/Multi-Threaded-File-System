#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <thread>
#include <filesystem>
#include <unordered_map>
#include "file_programming.cpp"
#include "main.cpp"

#define PORT 8080

using namespace std;

unordered_map<string, int> semaphore_map;

string scanCommand(Environment &env, char *buffer,int user_id) {
        env.initialize();

        vector<string> commands = string_splitter(buffer, ',');

        if (commands[0] == "mkdir") {
            env.Mk_Dir(commands[1]);
            return "Your Folder Was Created";
        }
        else if (commands[0] == "touch") {
            env.Create_File(commands[1]);
            return "Your File was Created";
        }
        else if (commands[0] == "write") {
            // Wait
            if (semaphore_map[commands[1]] == -1 || semaphore_map[commands[1]] > 0) return "This file is being used!";

            semaphore_map[commands[1]] = -1;
            env.Write_To_File(commands[1], commands[3], commands[2][0]);

            // Signal
            semaphore_map[commands[1]] = 0;

            return "Your File Was Written";
        }
        else if (commands[0] == "read") {
            if (semaphore_map[commands[1]] == -1) return "This file is being used!";
            semaphore_map[commands[1]]++;
            string content = env.See_File_Content(commands[1]);
            semaphore_map[commands[1]]--;
            return content;
        }
        else if (commands[0] == "rm_file") {
            if (semaphore_map[commands[1]] == -1 || semaphore_map[commands[1]] > 0) return "This file is being used!";
            semaphore_map[commands[1]] = -1;
            env.Delete_File(commands[1]);
            semaphore_map[commands[1]] = 0;
            return "Your File Was Deleted";
        }
        else if (commands[0] == "rm_folder") {
            env.Delete_Folder(commands[1]);
            return "Your Folder Was Deleted";
        }
        else if (commands[0] == "cd") {
            env.Ch_Dir(commands[1]);
            string response = "Folder Changed: ";
            response += env.Pwd();
            return response;
        }
        else if (commands[0] == "mv_file") {
            env.Move_File(commands[1], commands[2]);
            return "Your File Was Moved";
        }
        else if (commands[0] == "mv_folder") {
            env.Move_Folder(commands[1], commands[2]);
            return "Your Folder Was Moved";
        }
        else if (commands[0] == "ls") {
            string temp = env.Ls();
            if (temp.size() <= 0) {
                temp = "Folder Empty";
            }
            return temp;
        }
        else if (commands[0] == "current") {
            return env.Pwd().c_str();
        }
        else if (commands[0] == "memory_map") {
            return env.Show_Memory_Map();
        }
        else {
            return "Please Enter a Valid Command";
        }
}

// Main Functionality
void client_handler(int user_id) {
    prompt();

    Environment env;
    env.initialize();

    while (true) {
        int reader;
        char buffer[2048] = {0};
        reader = read(user_id, buffer, 2048);
        string feedback = scanCommand(env, buffer, user_id);
        send(user_id, (char *)feedback.c_str(), feedback.size(), 0);
    }
}

int main(int argument, char const *argv[])
{
    int obj_server, sock, reader;
    struct sockaddr_in address;
    int opted = 1;
    int address_length = sizeof(address);
    if ((obj_server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Opening of Socket Failed !");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(obj_server, SOL_SOCKET, SO_REUSEADDR,
                     &opted, sizeof(opted)))
    {
        perror("Can't set the socket");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(obj_server, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("Binding of socket failed !");
        exit(EXIT_FAILURE);
    }
    if (listen(obj_server, 5) < 0)
    {
        perror("Can't listen from the server !");
        exit(EXIT_FAILURE);
    }


    while (true)
    {
        sock = accept(obj_server, (struct sockaddr *)&address, (socklen_t *)&address_length);
        if (sock < 0) {
            cout << "Client Connection Unsuccessful";
        }
        else {
            thread t(client_handler, sock);
            t.detach();
        }
    }

    exit(0);
    return 0;
}