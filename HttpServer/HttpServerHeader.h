#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <WinSock2.h>
#define MAX_CONNECTIONS 100

#pragma comment(lib, "ws2_32.lib") // Подключаем библиотеку Winsock
#pragma warning(disable: 4996)

struct ThreadParams {
    int index;
    SOCKET Connections_Index[MAX_CONNECTIONS];
};

DWORD WINAPI ClientHandler(LPVOID lpParam);
