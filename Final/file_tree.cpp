#include <string>
#include <vector>
#include "file_node.cpp"
#include "folder_node.cpp"
#include "util.cpp"
#include <pthread.h>
using namespace std;

int getPages (float nodeSize) {
    return sysconf(_SC_PAGE_SIZE) / nodeSize;
}

// Tree Data Structure
class Tree
{
private:
    Folder_Node *root;
    ofstream myDatFile;

public:
    Tree()
    {
        // Constructor Function
        // Creating Root Node
        Folder_Node *temp = new Folder_Node("root");
        root = temp;

        float nodeSize = sizeof(root);
        
        myDatFile.open("memory.dat");
        myDatFile << "Root: " << &root << " Pages: " << getPages(nodeSize);
        myDatFile.close();
    }

    // Get Root
    Folder_Node* get_root()
    {
        return root;
    }

    // Adding New File to Current Directory
    void add_new_file(string file_path, string file_name, string file_extension, string content = "")
    {
        File_Node* temp = new File_Node(file_name, file_extension, content);
        Folder_Node* parent = find_folder_node(file_path);        
        parent->sub_files.push_back(temp);

        float nodeSize = sizeof(file_name);
        myDatFile.open("memory.dat", ios_base::app);
        myDatFile << "\n" << file_name << "." << file_extension << ": " << &temp << " Pages: " << getPages(nodeSize);
        myDatFile.close();
    }

    // Adding New Folder to Current Directory
    void add_new_folder(string folder_path, string folder_name)
    {
        Folder_Node* temp = new Folder_Node(folder_name);
        Folder_Node* parent = find_folder_node(folder_path);
        parent->sub_folders.push_back(temp);

        float nodeSize = sizeof(folder_name);
        myDatFile.open("memory.dat", ios_base::app);
        myDatFile << "\n" << folder_name<< ": " << &temp << " Pages: " << getPages(nodeSize);
        myDatFile.close();
    }

    // Find Folder Node in Non Binary Tree
    Folder_Node* find_folder_node(string folder_path)
    {
        // Splitting the Path
        vector<string> path = string_splitter(folder_path, '/');
        string end = path[path.size() - 1];
        Folder_Node* temp = root;
        for (int i = 0; i < path.size(); i++)
        {
            for (int j = 0; j < temp->sub_folders.size(); j++)
            {
                if (temp->sub_folders[j]->folder_name == path[i])
                {
                    temp = temp->sub_folders[j];
                    break;
                }
            }
        }
        if (temp->folder_name == end)
        {
            return temp;
        }
        else
        {
            return new Folder_Node("NULL");
        }
    }

    // Find File Node Non Binary Tree
    pair<Folder_Node*, File_Node*> find_file_node(string file_path, string file_name)
    {
        Folder_Node* temp = find_folder_node(file_path);
        File_Node* tempFile = NULL;
        for (auto file : temp->sub_files)
        {
            if (file->file_name == file_name)
            {
                tempFile = file;
                break;
            }
        }
        if (tempFile == NULL)
        {
            return make_pair(temp, new File_Node("NULL", "NULL"));
        }
        else
        {
            return make_pair(temp, tempFile);
        }
    }

    // Delete File Node
    void delete_file(string file_path, string file_name)
    {
        Folder_Node* file = find_folder_node(file_path);
        for (int i = 0; i < file->sub_files.size(); i++)
        {
            if (file->sub_files[i]->file_name == file_name)
            {
                delete file->sub_files[i];
                file->sub_files.erase(file->sub_files.begin() + i);
                break;
            }
        }
    }

    // Delete Folder Node
    void delete_folder(string folder_path, string folder_name)
    {
        Folder_Node* folder = find_folder_node(folder_path);
        for (int i = 0; i < folder->sub_folders.size(); i++)
        {
            if (folder->sub_folders[i]->folder_name == folder_name)
            {
                delete folder->sub_folders[i];
                folder->sub_folders.erase(folder->sub_folders.begin() + i);
                break;
            }
        }
    }

    // List All Files and Folders
    string list_all(string folder_path)
    {
        Folder_Node* folder = find_folder_node(folder_path);
        string output = "";
        for (auto file : folder->sub_files)
        {
            output += file->file_name;
            output += ".";
            output += file->file_extension;
            output += " ";
        }
        for (auto folder : folder->sub_folders)
        {
            output += folder->folder_name;
            output += " ";
        }
        return output;
    }

    // Write To File
    bool write_to_file(string file_path, string file_name, string content)
    {
        pair<Folder_Node*, File_Node*> file = find_file_node(file_path, file_name);
        if (file.second->file_name == "NULL")
        {
            return false;
        }
        else
        {
            file.second->content = content;
            return true;
        }
    }

    // See File Content
    string see_file_content(string file_path, string file_name)
    {
        pair<Folder_Node*, File_Node*> file = find_file_node(file_path, file_name);
        if (file.second->file_name == "NULL")
        {
            return "NULL";
        }
        else
        {
            return file.second->content;
        }
    }

    // Move File
    bool move_file(string file_path, string file_name, string new_file_path)
    {
        pair<Folder_Node*, File_Node*> file = find_file_node(file_path, file_name);
        Folder_Node* new_folder = find_folder_node(new_file_path);
        if (new_folder->folder_name == "NULL")
            return false;
        File_Node* new_file_node = new File_Node(file.second->file_name, file.second->file_extension, file.second->content);
        new_folder->sub_files.push_back(new_file_node);
        delete_file(file_path, file_name);
        return true;
    }

    // Show Memory Map
    string show_memory_map()
    {
        string memoryMap = "";
        string line;
        ifstream myDatFile;
        myDatFile.open("memory.dat");
        while (getline(myDatFile, line)) {
            memoryMap += line;
            memoryMap += "\n";
        }
        return memoryMap;
    }

    // Move Folder
    bool move_folder(string folder_path, string folder_name, string new_folder_path)
    {
        Folder_Node* folder = find_folder_node(folder_path + "/" + folder_name);
        Folder_Node* new_folder = find_folder_node(new_folder_path);
        if (new_folder->folder_name == "NULL")
            return false;
        Folder_Node* new_folder_node = folder;
        new_folder->sub_folders.push_back(new_folder_node);
        delete_folder(folder_path, folder_name);
        return true;
    }
};