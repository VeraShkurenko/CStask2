//Main.cpp
#include <iostream>
#include "Socket.h"
#include <vector>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int nChoice;
	int port = 24242; //�������� ����
	string ipAddress = "127.0.0.1"; //����� �������

	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//��������� ������
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//�������� ������ �� �������
			//� ��������� � ���������� receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			//// !!!! 
			
			if (strcmp(receiveMessage, "Menu") == 0)
			{
				string menu = "1. ����(30���)\n2. �������� ��(40���)\n3. ��������(25���)\n������� ����������: ����� ������� - �������\n";
				server.SendDataMessage(menu);
			} 
			else if (strstr(receiveMessage, "1") || strstr(receiveMessage, "2") || strstr(receiveMessage, "3"))
			{
				vector<int> nums;
				static int price[] {30, 40, 25};
				int sum = 0;
				
				char buf[10];
				int len = 0;
				for (char c : receiveMessage)
				{
					if (c >= 48 && c <= 57)
					{
						buf[len] = c;
						len++;
					}
					else {
						if (len != 0)
						{
							nums.push_back(stoi(buf));
							len = 0;
							for (int i = 0; i < 10; i++) buf[i] = '\0';
						}
					}
				}
				for (int i = 0; i < nums.size()-1; i+=2)
				{
					sum += nums[i + 1] * price[nums[i]-1];
				}
				server.SendDataMessage("���� ����������: " + to_string(sum) + "���");
			}
			else 
			{
				//���������� ������ �������
				cout << "������� ������ ��� �������� ";
				char buff[100];
				cin.ignore();
				cin.get(buff, 100);

				server.SendDataMessage(buff); // server.SendDataMessage(string str); ���������� !!!

				//���� ���� ��������� "end", ��������� ������

				if (strcmp(receiveMessage, "end") == 0 ||
					strcmp(sendMessage, "end") == 0)
					break;
			}
		}
	}
	else if (nChoice == 2)
	{
		cout << "IP address = 127.0.0.1 " << endl;
			
		ClientSocket client;
		//������������ � �������
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			//���������� ���������
		//���������� ������ �������
			cout << "������� ������ ��� �������� ";
			char buff[100];
			cin.ignore();
			cin.get(buff,100);
		
			client.SendDataMessage(buff);

			cout << "\tWaiting" << endl;

			//�������� �����
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//��������� ����������
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










