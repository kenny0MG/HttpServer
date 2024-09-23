#include "HttpServerHeader.h"

DWORD WINAPI ClientHandler(LPVOID lpParam){
	ThreadParams* params = (ThreadParams*)lpParam;
	int index = params->index;
	SOCKET Connections = params->Connections_Index[index];
	

	int msg_size;
	while (true) {
		recv(Connections, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections, msg, msg_size, NULL);
		for (int i = 0; i < 100; i++) {
			if (i == index) { // Проверяем, если это текущее соединение
				continue;
			}
			send(params->Connections_Index[i], (char*)&msg_size, sizeof(int), NULL);
			send(params->Connections_Index[i], msg, msg_size, NULL); // Отправляем сообщение всем, кроме текущего клиента
		}
		delete[] msg;
		
	}
	delete params;
}