#include <iostream>
#include <dirent.h>
#include <fstream>
#include <cstring>
#include "file_tree.cpp"
using namespace std;


class Environment
{
private:
    Tree *tree;
    string current_path;

    void myfilerecursive(string basePath)
    {
        string path;
        struct dirent *dp;
        const char* base = basePath.c_str();
        DIR *dir = opendir(base);

    
        if (!dir)
            return;

        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {
                path = basePath;
                string dirPath = string_splitter(path, '.')[1];
                path += "/";
                path += dp->d_name;
                // If Folder
                if (string_splitter(dp->d_name, '.').size() == 1) {
                    tree->add_new_folder(dirPath, dp->d_name);
                }
                // IF File
                else {
                    // Reading File Content
                    string file_content = "";
                    ifstream file(path);
                    string line;
                    while (getline(file, line))
                    {
                        file_content += line;
                    }
                    file.close();
                    tree->add_new_file(dirPath, string_splitter(dp->d_name, '.')[0], string_splitter(dp->d_name, '.')[1], file_content);
                }
                myfilerecursive(path);
            }
        }

        closedir(dir);
    }

public:
    Environment()
    {
        tree = new Tree();
        current_path = "root";
    }

    // Initializing
    void initialize()
    {
        // ReInitialize
        this->tree = new Tree();

        bool isRoot = false;
        // Checking If Root Exists
        for (const auto & entry : filesystem::directory_iterator("./"))
            if (entry.path() == "./root") 
            {
                isRoot = true;
                break;
            }
        if (isRoot) 
        {
            myfilerecursive("./root");
        }
        else 
        {
            system("mkdir root");
        }
    }

    // Adding New File to Current Directory
    void Create_File(string file_name) {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            cout << "Invalid File Name or Extension" << endl;
        }
        else {
            tree->add_new_file(current_path, file_name_split[0], file_name_split[1]);
            system(("touch " + current_path + "/" + file_name).c_str());
        }
    }

    // Deleting New File in Current Directory
    void Delete_File(string file_name) 
    {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            cout << "Invalid File Name or Extension" << endl;
        }
        else {
            tree->delete_file(current_path, file_name_split[0]);
            system(("rm " + current_path + "/" + file_name).c_str());
        }
    }

    // Deleting New Folder in Current Directory
    void Delete_Folder(string folder_name) 
    {
        if (folder_name == "") 
        {
            cout << "Invalid Folder Name" << endl;
        }
        else {
            tree->delete_folder(current_path, folder_name);
            system(("rmdir " + current_path + "/" + folder_name).c_str());
        }
    }

    // Adding New Folder to Current Directory
    void Mk_Dir(string folder_name) 
    {
        if (folder_name == "") 
        {
            cout << "Invalid Folder Name" << endl;
        }
        else {
            tree->add_new_folder(current_path, folder_name);
            system(("mkdir " + current_path + "/" + folder_name).c_str());
        }
    }

    // Changing Directory
    void Ch_Dir(string folder_name) 
    {
        // Moving to Root if '.'
        if (folder_name == ".") 
        {
            current_path = "root";
            return;
        }
        // Moving to Parent if '..'
        if (folder_name == "..") 
        {
            vector<string> path = string_splitter(current_path, '/');
            current_path = "";
            for (int i = 0; i < path.size() - 1; i++) 
            {
                current_path += path[i] + "/";
            }
            return;
        }


        if (folder_name == "") 
        {
            cout << "Invalid Folder Name" << endl;
        }
        else {
            current_path = current_path + "/" + folder_name;
        }
    }

    // Listing Files and Folders in Current Directory
    string Ls() 
    {
        string output = tree->list_all(current_path);
        return output;
    }

    // Write To File
    void Write_To_File(string file_name, string content, char mode) 
    {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            cout << "Invalid File Name or Extension" << endl;
        }
        else {


            bool isWritten = tree->write_to_file(current_path, file_name_split[0], content);
            if (isWritten) 
            {
                if (mode == 'w') {
                    system(("echo " + content + " > " + current_path + "/" + file_name).c_str());
                }
                else if (mode == 'a') {
                    system(("echo " + content + " >> " + current_path + "/" + file_name).c_str());
                }
            }
        }
    }

    // See File Content
    string See_File_Content(string file_name) 
    {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            return "Invalid File Name or Extension";
        }
        else {
            string content = tree->see_file_content(current_path, file_name_split[0]);
            return content;
        }
    }

    // Move File
    void Move_File(string file_name, string destination) 
    {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            cout << "Invalid File Name or Extension" << endl;
        }
        else {
            bool isMoved = tree->move_file(current_path, file_name_split[0], destination);
            if (isMoved) 
            {
                system(("mv " + current_path + "/" + file_name + " " + destination).c_str());
            }
        }
    }

    // Move Folder
    void Move_Folder(string folder_name, string destination) 
    {
        if (folder_name == "") 
        {
            cout << "Invalid Folder Name" << endl;
        }
        else {
            bool isMoved = tree->move_folder(current_path, folder_name, destination);
            if (isMoved) 
            {
                system(("mv " + current_path + "/" + folder_name + " " + destination).c_str());
            }
        }
    }

    // Opening File
    void Open_File(string file_name) 
    {
        vector<string> file_name_split = string_splitter(file_name, '.');
        if (file_name == "" || file_name_split.size() == 1) 
        {
            cout << "Invalid File Name or Extension" << endl;
        }
        else {
            system(("gedit " + current_path + "/" + file_name).c_str());
        }
    }

    // Show Memory Map
    string Show_Memory_Map() 
    {
        return tree->show_memory_map();
    }

    string Pwd() 
    {
        return current_path;
    }
};