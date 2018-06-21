#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
using namespace std;
int main()
{
    int client;
    int portNum = 1800;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "192.168.11.93";
    struct sockaddr_in server_addr;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0)
    {
        cout << "\nLỗi khi thiết lập ổ cắm ..." << endl;
        exit(1);
    }
    cout << "\n=> Ứng dụng Socket đã được tạo ..." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    server_addr.sin_addr.s_addr = inet_addr("192.168.11.93");

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
    cout << "=> Kết nối với số cổng của máy chủ: " << portNum << endl;
    cout << "=> Đang chờ xác nhận từ máy chủ ..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> kết nối xác nhận, bạn có thể giao tiếp ...";
    cout << "\n\n=> Nhập # để kết thúc kết nối\n" << endl;
    do {
        cout << "Client: ";
        do {
            cin >> buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);
        cout << "Server: ";
        do {
            recv(client, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);
        cout << endl;
    } while (!isExit);
    cout << "\n=> Đã ngắt kết nối.\nGoodbye...\n";
    close(client);
    return 0;
}
