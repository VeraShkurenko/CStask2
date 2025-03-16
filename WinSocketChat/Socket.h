#pragma once
#include <iostream>
#include <string>
#include "WinSock2.h" //����� ��������� ����������, �����������
//��� Winsock 2 API.
#include <ws2tcpip.h> //�������� ������� ��� ������ � ��������
//����. inet_pton
#pragma comment(lib, "Ws2_32.lib") //������� ���������� Windows Sockets

using namespace std;

const int MAXSTRLEN = 255;

class Socket
{
protected:
	WSADATA wsaData;//��������� ��� �������� ���������� � ������������� �������
	SOCKET _socket; //���������� ���������� ������
	SOCKET acceptSocket;//���������� ������, ������� ������ � �������� 
	sockaddr_in addr; //��������� ����� � ����
public:
	Socket();
	~Socket();
	bool SendData(const char*); //����� ��� �������� ������ � ����
	bool ReceiveData(char*, int);//����� ��� ��������� ������
	void CloseConnection(); //����� ��� �������� ����������
	void SendDataMessage(const char * str);//����� ��� �������� ��������� ������������
	void SendDataMessage(string str);//����� ��� �������� ��������� ������������
};

class ServerSocket : public Socket
{
public:
	void Listen(); //����� ��� ��������� "����������" ������
	void Bind(int port); //����� ��� �������� ������ � �����
	void StartHosting(int port); //���������� ����� ���� ���������� �������
};

class ClientSocket : public Socket
{
public:
	//����� ��� ����������� � �������
	void ConnectToServer(const char * ip, int port);
};











