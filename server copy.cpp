#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int main()
{
	int client, server;
	int portNum = 1600;
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];
	struct sockaddr_in server_addr;
	socklen_t size;
	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);
	if(client < 0){
		cout << "Lỗi khi thiết lập kết nối." << endl;
		exit(1);
	}
	cout << "Đã tạo kết nối socket máy chủ .." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);
    if(bind(client,(struct sockaddr*)&server_addr, sizeof(server_addr))<0){
    	cout << "Lỗi kết nối ổ cắm ..." << endl;
    	exit(1);
    }
    size = sizeof(server_addr);
    cout << "đang khóa cho khách hàng ..." << endl;
    //listening socket
    listen(client, 1);
    //Accept client
    server = accept(client, (struct sockaddr*)&server_addr, &size);
    if(server<0){
    	cout << "Lỗi khi chấp nhận ..." << endl;
    	exit(1);
    }
    while(server>0){
    	strcpy(buffer, "server connected...\n");
    	send(server, buffer, bufsize, 0);
    	cout << "kết nối với khách hàng ...." << endl;
    	cout << "nhâp # để kết thúc kết nối..." << endl;
		cout << "Client: ";
		do{
			recv(server, buffer, bufsize, 0);
			cout << buffer << " ";
			if(*buffer == '#'){
				*buffer = '*';
				isExit = true;
			}
		}while(*buffer != '*');
		do{
			cout << "\nServer: ";
			do{
				cin >> buffer;
				send(server, buffer, bufsize, 0);
				if(*buffer == '#'){
					send(server, buffer, bufsize, 0);
					*buffer = '*';
					isExit = true;
				}
			}while(*buffer != '*');

			cout << "Client: ";
			do{
				recv(server, buffer, bufsize, 0);
				cout << buffer << " ";
				if(*buffer == '#'){
					*buffer == '*';
					isExit = true;
				}
			}while(*buffer != '*');
		}while(!isExit);
		cout << "đã kết nối xong..." << endl;
		cout << "Goodbye.." << endl;
		exit(1);
    }
    close(client);
    return 0;
}
