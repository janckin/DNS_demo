// windowsSocket.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <iostream>
#include "DNSHashmap.h"
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

SOCKET sockServer, sockClient;
SOCKADDR_IN addrServer, addrClient;
int naddr = sizeof(SOCKADDR_IN);
const int BUF_SIZE = 1024;

char* sendbuf;
char recvbuf[BUF_SIZE];
char* error = "no such ip address";
int hash;
int length;


int main(int argc, char* argv[])
{
	// ��ʼ��DNS��ϣ��
	struct hashData* hashTable = (hashData*)malloc(35 * MAXHASH);
	initHash(hashTable, 200);

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if(WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 0;
	}
	//����Socket
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
    // ��ʼ����ַ��
	addrServer.sin_addr.s_addr = inet_addr("192.168.1.100");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(9080);

	// �󶨿ͻ���
	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer));

	while(1)
	{	
		// ��������
		listen(sockServer, 5);
		// ������������
		sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &naddr);

		if(sockClient != INVALID_SOCKET) // ���ӳɹ�
		{
			printf("connect success\n");
			// ��ȡ�ͻ��˷��͵�����
			while(1){
				int read = recv(sockClient, recvbuf, sizeof(recvbuf), 0);

				// ��ӡ�ͻ������ݣ���������Ӧ��Ϣ
				if(read > 0){
					hash = findHash(hashTable, recvbuf);
					if(hash != -1)
					{
						sendbuf = hashTable[hash].ip;
					}
					else
					{
						sendbuf = error;

					}

					send(sockClient, sendbuf, strlen(sendbuf), 0);
					sendbuf = 0;
				}
				if(read == 0)
				{
					break;
				}
			}

			closesocket(sockClient);
			
		}

	}

	return 1;

}