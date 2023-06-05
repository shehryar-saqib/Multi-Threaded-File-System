#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

// Utility Functions
// Split String into Vector of Strings
vector<string> string_splitter(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

string get_command(string line) {
    string command = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            break;
        }
        command += line[i];
    }
    return command;
}
