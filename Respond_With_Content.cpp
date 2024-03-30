/*
  In this program we extract the path from the HTTP request.

      - Content of HTTP request look's like :
        GET /index.html HTTP/1.1
        Host: localhost:4221
        User-Agent: curl/7.64.1

    GET /index.html HTTP/1.1 is the start line.
    GET is the HTTP method.
    /index.html is the path.
    HTTP/1.1 is the HTTP version.
    Host: localhost:4221 and User-Agent: curl/7.64.1 are HTTP headers.


    TASK : If the path is /, you'll need to respond with a 200 OK response.
  Otherwise, you'll need to respond with a 404 Not Found response.
*/
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

constexpr int SERVER_PORT = 4221;
constexpr int CONNECTION_BACKLOG = 5;
constexpr int BUFFER_SIZE = 512;

int createServerSocket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create server socket\n";
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void setSocketOptions(int server_fd) {
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed\n";
        exit(EXIT_FAILURE);
    }
}

void bindServerSocket(int server_fd) {
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to bind to port " << SERVER_PORT << std::endl;
        exit(EXIT_FAILURE);
    }
}

int acceptClientConnection(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    std::cout << "Waiting for a client to connect...\n";
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        std::cerr << "Failed to connect with client\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Client connected\n";
    return client_fd;
}

std::string receiveData(int client_fd) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        std::cerr << "Failed to receive data from client\n";
        exit(EXIT_FAILURE);
    }
    return std::string(buffer, bytes_received);
}

void sendData(int client_fd, const std::string& data) {
    int bytes_sent = send(client_fd, data.c_str(), data.size(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Failed to send data to client\n";
    } else {
        std::cout << "Sent " << bytes_sent << " bytes to client." << std::endl;
    }
}

void closeSocket(int sockfd) {
    close(sockfd);
}

std::string extractPath(const std::string& request) {
    int i = request.find_first_of('/');
    std::string path = request.substr(i);
    int j = path.find_first_of(' ');
    return path.substr(0, j);
}

std::string generateResponse(const std::string& path) {
    std::string OK = "HTTP/1.1 200 OK\r\n\r\n";
    std::string PLAINTEXT = "Content-Type: text/plain";
    std::string CONTENT_LENGTH = "Content-Length: ";
    std::string NOT_FOUND = "HTTP/1.1 404 Not Found\r\n\r\n";
    std::string ECHO = "/echo";

    if (path == "/") {
        return OK;
    } else if (path.compare(0, ECHO.size(), ECHO) == 0) {
        std::string to_echo = path.substr(6);
        return OK + '\n' + PLAINTEXT + '\n' + CONTENT_LENGTH +
               std::to_string(to_echo.size()) + "\n\n" + to_echo + '\n';
    } else {
        return NOT_FOUND;
    }
}

int main(int argc, char **argv) {
    int server_fd = createServerSocket();
    setSocketOptions(server_fd);
    bindServerSocket(server_fd);

    if (listen(server_fd, CONNECTION_BACKLOG) != 0) {
        std::cerr << "listen failed\n";
        closeSocket(server_fd);
        exit(EXIT_FAILURE);
    }

    int client_fd = acceptClientConnection(server_fd);
    std::string request = receiveData(client_fd);
    std::string path = extractPath(request);
    std::string response = generateResponse(path);
    sendData(client_fd, response);

    closeSocket(client_fd);
    closeSocket(server_fd);

    return 0;
}
