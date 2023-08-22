#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "cJSON/cJSON.h"

// using namespace std;

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
	char *out;cJSON *json;
	
	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);
		free(out);
	}
}

int main(void)
{
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // 设置服务器信息
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8188);  // 服务器端口
    serverAddress.sin_addr.s_addr = inet_addr("172.28.48.1");  // 服务器IP地址

    // 连接到服务器
    int connectResult = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (connectResult == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // 向服务器发送数据
    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    // 接收服务器回复
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Server says: " << buffer << std::endl;

    doit(buffer);

    // 关闭套接字
    close(clientSocket);
    return 0;
}