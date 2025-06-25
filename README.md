# Multi-Threaded File System

A lightweight C++ file server/client using POSIX sockets and multithreading.

## Features

* **Concurrent Clients**: TCP server (port 8080) handles multiple clients with `std::thread`/`pthread`.
* **File Ops**: Create, delete, move, read, write files and directories.
* **Persistence**: File tree saved/loaded via `memory.dat`.
* **Sample Data**: Example structure in `Final/root`.

## Structure

```
Multi-Threaded-File-System/
├── .gitattributes
└── Final/
    ├── server.cpp, client.cpp, main.cpp, file_*.cpp, util.cpp
    ├── memory.dat
    └── root/ (sample files)
```

## Prerequisites

* Linux/Unix OS
* C++17 compiler
* POSIX sockets support

## Build & Run

```bash
cd Final
# Build
g++ -std=c++17 server.cpp main.cpp file_programming.cpp file_tree.cpp file_node.cpp folder_node.cpp util.cpp -o server -pthread
g++ -std=c++17 client.cpp -o client

# Run
./server      # start server on port 8080
./client      # connect client (repeat for multiple)
```

## Client Commands

```txt
create <file>
delete <file>
mkdir <dir>
cd <dir>
ls
read <file>
write <file> <text>
move <src> <dst>
exit
```

## License

For educational use.
