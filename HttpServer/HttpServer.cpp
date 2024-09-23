#include <iostream>
#include <vector>
#include <string>
#include <WinSock2.h>
#include "HttpServerHeader.h"

#pragma comment(lib, "ws2_32.lib") // Подключаем библиотеку Winsock
#pragma warning(disable: 4996)


using namespace std;

SOCKET Connections[100];
unsigned Counter = 0;



int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	char buffer[256];
	//Структура для передачи данных
	ThreadParams* params = new ThreadParams;


	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8080);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;	

	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			cout << "Error client connection\n";
		}
		else {
			cout << "Client Connection!!!\n";
			cout << "Client !" << Counter << " " << "\n";
			++Counter;
			int valread = recv(newConnection, buffer, sizeof(buffer), 0);
			if (valread >= 0) {
				buffer[valread] = '\0'; // Завершение строки
				std::cout << "Received IP: " << buffer << std::endl;
			}
			string response = "Hi!";
			int msg_size = response.size();
			send(newConnection, (char*)&msg_size,sizeof(int), NULL);
			send(newConnection, response.c_str(), response.size(), NULL);
			Connections[i] = newConnection;
			//Передаем данные в функцию ClientHandler через структуру ThreadParams
			params->index = i;
			params->Connections_Index[params->index] = Connections[i];

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(params), NULL, NULL);


		}
	}
	
	


	system("pause");

}