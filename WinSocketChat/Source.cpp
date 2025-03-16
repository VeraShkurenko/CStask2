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
	int port = 24242; //выбираем порт
	string ipAddress = "127.0.0.1"; //Адрес сервера

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
		//Запускаем сервер
		server.StartHosting(port);
		while (true)
		{
			cout << "\tWaiting..." << endl;
			//Получаем данные от клиента
			//и сохраняем в переменной receiveMessage
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			//// !!!! 
			
			if (strcmp(receiveMessage, "Menu") == 0)
			{
				string menu = "1. кола(30грн)\n2. картопля фрі(40грн)\n3. морозиво(25грн)\nПриклад замовлення: Номер позиції - кількість\n";
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
				server.SendDataMessage("Сума замовлення: " + to_string(sum) + "грн");
			}
			else 
			{
				//Отправляем данные клиенту
				cout << "Введите строку для отправки ";
				char buff[100];
				cin.ignore();
				cin.get(buff, 100);

				server.SendDataMessage(buff); // server.SendDataMessage(string str); переделать !!!

				//Если есть сообщение "end", завершаем работу

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
		//подключаемся к серверу
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			//отправляем сообщение
		//Отправляем данные клиенту
			cout << "Введите строку для отправки ";
			char buff[100];
			cin.ignore();
			cin.get(buff,100);
		
			client.SendDataMessage(buff);

			cout << "\tWaiting" << endl;

			//получаем ответ
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << "Received: " << receiveMessage << endl;
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//Закрываем соединение
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}










