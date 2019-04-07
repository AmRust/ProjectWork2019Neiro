#pragma once
#pragma comment (lib,"Ws2_32.lib")

#include "NetworkX.hpp"

int connectSock(SOCKET CS, const struct sockaddr* sockAdd, int sizeofServerAddr)
{
	return (connect(CS, sockAdd, sizeofServerAddr));
}

NetworkX::NetworkX(QString threadName) :
    name(threadName){}
 
NetworkX::~NetworkX()
{
	terminate();
}

void NetworkX::run()
{
	while (true)
	{
		WSADATA wsaData;
		SOCKET ConnectSocket;  // ���������� ����� � ����� ��� ��������
		sockaddr_in ServerAddr;  // ��� ����� ����� �������
		int err, maxlen = 512;  // ��� ������ � ������ �������
		char* recvbuf = new char[maxlen];  // ����� ������

		bool run_flag = TRUE;

		// ������������� Winsock
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		// ����������� � �������
		ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		ServerAddr.sin_port = htons(12345);

		qDebug() << "Trying to connect...";
		err = connectSock(ConnectSocket, (sockaddr *)&ServerAddr, sizeof(ServerAddr));

		while (err == SOCKET_ERROR)
		{
			err = connectSock(ConnectSocket, (sockaddr *)&ServerAddr, sizeof(ServerAddr));
		}

		qDebug() << "Connection open.";

		while (run_flag)
		{
			try {
				err = recv(ConnectSocket, recvbuf, maxlen, 0);
				recvbuf[err] = 0;
				std::string stroka(recvbuf);
				int data = std::stoi(stroka);
				if (err > 0) {
					qDebug() << "Data: " << data ;
					emit InputData(data);
				}
				else
				{
					//printf("Connection closing...\n");
					qDebug() << "Connection closing...";
					break;
				}
			}
			catch (...) {
				qDebug() << "Error! Reconnect...";
				break;
			}
			
		}

		// ���������� ����������
		closesocket(ConnectSocket);
		WSACleanup();
	}
}
