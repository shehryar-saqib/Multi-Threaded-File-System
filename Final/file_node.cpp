#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class File_Node
{
    public:
    int type;               // Folder Type
    string file_name;        // File Name
    string file_extension;   // File Extension, Empty for Folders
    string content;         // File Content
    
    File_Node (string file_name = "", string file_extension = "", string content = "") {
        this->file_name = file_name;
        this->file_extension = file_extension;
        this->content = content;
        this->type = 1;
    }
    
};