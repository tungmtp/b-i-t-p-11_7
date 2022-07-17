// HTTPServer1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);
    char buf[2048];
    int ret;
    while (1)
    {
        // Chap nhan ket noi
        SOCKET client = accept(listener, NULL, NULL);
        // Nhan yeu cau
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            closesocket(client);
            continue;
        }
        // Xu ly yeu cau
        if (ret < sizeof(buf))
            buf[ret] = 0;
        printf("%s\n", buf);
        if (strncmp(buf, "GET /web", 8) == 0)
        {
            const char* header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            send(client, header, strlen(header), 0);
            FILE* f = fopen("C:\\test_server\\test.html", "rb");
            while (!feof(f))
            {
                ret = fread(buf, 1, sizeof(buf), f);
                if (ret <= 0)
                    break;
                send(client, buf, ret, 0);
            }
            fclose(f);
        }
        else if (strncmp(buf, "GET /image", 10) == 0)
        {
            const char* header = "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n";
            send(client, header, strlen(header), 0);
            FILE* f = fopen("C:\\test_server\\test.jpg", "rb");
            while (!feof(f))
            {
                ret = fread(buf, 1, sizeof(buf), f);
                if (ret <= 0)
                    break;
                send(client, buf, ret, 0);
            }
            fclose(f);
        }
        else if (strncmp(buf, "GET /audio", 10) == 0)
        {
            const char* header = "HTTP/1.1 200 OK\r\nContent-Type: audio/mp3\r\n\r\n";
            send(client, header, strlen(header), 0);
            FILE* f = fopen("C:\\test_server\\test.mp3", "rb");
            while (!feof(f))
            {
                ret = fread(buf, 1, sizeof(buf), f);
                if (ret <= 0)
                    break;
                send(client, buf, ret, 0);
            }
            fclose(f);
        }
        else if (strncmp(buf, "GET /video", 10) == 0)
        {
            const char* header = "HTTP/1.1 200 OK\r\nContent-Type: video/mp4\r\n\r\n";
            send(client, header, strlen(header), 0);
            FILE* f = fopen("C:\\test_server\\test.mp4", "rb");
            while (!feof(f))
            {
                ret = fread(buf, 1, sizeof(buf), f);
                if (ret <= 0)
                    break;
                send(client, buf, ret, 0);
            }
            fclose(f);
        }
        else
        {
            // Tra lai ket qua
            const char* res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello World</h1></body></html>";
            send(client, res, strlen(res), 0);
        }

        // Dong ket noi
        closesocket(client);

    }
    WSACleanup();
}