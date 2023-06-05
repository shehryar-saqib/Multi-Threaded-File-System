#include <iostream>
#include <string>
#include <vector>
#include "file_node.cpp"
using namespace std;
class Folder_Node
{
    public:
    int type;   // Folder Type
    string folder_name; // File Name
    vector<Folder_Node*> sub_folders; // Sub Folders
    vector<File_Node*> sub_files; // Sub Files
    
    Folder_Node(string folder_name) {
        this->type = 0;
        this->folder_name = folder_name;
        this->sub_files = sub_files;
        this->sub_folders = sub_folders;
    }
};