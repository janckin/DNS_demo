// clientSocket.cpp : Defines the entry point for the console application.


#include <stdio.h>
#include <iostream.h>
#include <cstring>
 
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

SOCKET sockServer, sockClient;
SOCKADDR_IN addrServer, addrClient;
int naddr = sizeof(SOCKADDR_IN);
const int BUF_SIZE = 1024;
char sendbuf[BUF_SIZE];


int main(int argc, char* argv[])
{

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if(WSAStartup(socketVersion, &wsaData) != 0)
	{
		return 0;
	}
	//����Socket
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
    // ��ʼ���ͻ��˵�ַ��
	addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(8080);
	bind(sockClient, (SOCKADDR*)&addrClient, sizeof(addrClient));

	// ��ʼ����������ַ��
	addrServer.sin_addr.s_addr = inet_addr("192.168.1.100");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(9080);
	
	// �ͻ����������ӷ�����
	if(connect(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer)) != SOCKET_ERROR)
	{
		while(1)
		{
			// �ͻ��˴Ӽ��̶������ݣ������͸���������Ȼ���ȡ��Ӧ��Ϣ
			cout << "input your domain address:" << endl;
			cin >> sendbuf;
			char recvbuf[BUF_SIZE] = {0}; //ÿ�ζ���������һ���������飬���⽫�ϴ�δ���ǵĽ�����

			//����������close�ͷ������ݣ������������ر�socket
			if(strcmp(sendbuf, "close"))
			{
				int senddata = send(sockServer, sendbuf, sizeof(sendbuf), 0);
				recv(sockServer, recvbuf, sizeof(recvbuf), 0);
				printf("%s\n", recvbuf);
				
			}
			else
			{ 
				break;
			}
		}

		closesocket(sockServer);
		closesocket(sockClient);
	}
	
	return 0;
}
