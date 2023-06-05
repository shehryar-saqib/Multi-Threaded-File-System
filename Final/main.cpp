#include <iostream>
// #include <filesystem>
// #include "file_programming.cpp"

// using namespace std;

// int main()
// {
//     Environment env;
//     env.initialize();
//     while (true) {
//         system("clear");
//         cout << "********************File Management System********************" << endl;
//         cout << "1. Create New File" << endl;
//         cout << "2. Create New Folder" << endl;
//         cout << "3. Delete File" << endl;
//         cout << "4. Change Folder" << endl;
//         cout << "5. Open File" << endl;
//         cout << "6. Move File" << endl;
//         cout << "7. Move Folder" << endl;
//         cout << "8. List All Directories" << endl;
//         cout << "9. Current Directory" << endl;
//         cout << "10. Exit" << endl;


//         int choice;
//         string name;
//         string destination;
//         cout << "Enter Your Choice: ";
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//             cout << "Enter File Name: ";
//             cin >> name;
//             env.Create_File(name);
//             break;
//         case 2:
//             cout << "Enter Folder Name: ";
//             cin >> name;
//             env.Mk_Dir(name);
//             break;
//         case 3:
//             cout << "Enter File Name: ";
//             cin >> name;
//             env.Delete_File(name);
//             break;
//         case 4:
//             cout << "Enter Folder Name: ";
//             cin >> name;
//             env.Ch_Dir(name);
//             break;
//         case 5:
//             cout << "Enter File Name: ";
//             cin >> name;
//             env.Open_File(name);
//             break;
//         case 6:
//             cout << "Enter File Name: ";
//             cin >> name;
//             cout << "Enter Destination: ";
//             cin >> destination;
//             env.Move_File(name, destination);
//             break;
//         case 7:
//             cout << "Enter Folder Name: ";
//             cin >> name;
//             cout << "Enter Destination: ";
//             cin >> destination;
//             env.Move_Folder(name, destination);
//             break;
//         case 8:
//             env.Ls();
//             break;
//         case 9:
//             env.Pwd();
//             break;
//         case 10:
//             cout << "Enter File Name: ";
//             cin >> name;
//             env.Write_To_File(name);
//             break;
//         case 11:
//             exit(0);
//             break;
//         default:
//             break;
//         }
//         cout << "Press Enter to Continue...";
//         cin.ignore();
//         cin.get();
//     }
// }

void prompt() {
    system("clear");
    cout << "********************File Management System********************" << endl;
    cout << "1. Create New File ~ touch *File Name*" << endl;
    cout << "2. Create New Folder ~ mkdir *Folder Name*" << endl;
    cout << "3. Delete File  ~ rm *File Name*" << endl;
    cout << "4. Change Folder ~ cd *Folder Name*" << endl;
    cout << "5. Open File" << endl;
    cout << "6. Move File" << endl;
    cout << "7. Move Folder" << endl;
    cout << "8. List All Directories" << endl;
    cout << "9. Current Directory" << endl;
    cout << "10. Exit ~ close" << endl;   
}