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

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cerr << "Failed to create server socket\n";
    return 1;
  }
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) <
      0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(4221);
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) !=
      0) {
    std::cerr << "Failed to bind to port 4221\n";
    return 1;
  }
  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  std::cout << "Waiting for a client to connect...\n";
  int client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                         (socklen_t *)&client_addr_len);
  if (client_fd < 0) {
    std::cerr << "Failed to connect with client\n";
    return 1;
  }
  char buffer[512];
  int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
  if (bytes_received < 0) {
    std::cerr << "Failed to receive data from client\n";
    close(client_fd);
    close(server_fd);
    return 1;
  }
  std::cout << "Received " << bytes_received << " bytes from client:\n"
            << buffer << std::endl;
  std::string request = std::string(buffer);
  int i = request.find_first_of('/');
  std::string path = request.substr(i);
  int j = path.find_first_of(' ');
  path = path.substr(0, j);
  std::cout << "PATH " << path << std::endl;
  std::string OK = "HTTP/1.1 200 OK\r\n\r\n";
  std::string NOT_FOUND = "HTTP/1.1 404 Not Found\r\n\r\n";
  int bytes_sent;
  if (path == "/") {
    bytes_sent = send(client_fd, OK.c_str(), OK.size(), 0);
  } else {
    bytes_sent = send(client_fd, NOT_FOUND.c_str(), NOT_FOUND.size(), 0);
  }
  if (bytes_sent < 0) {
    std::cerr << "Failed to send data to client\n";
  } else {
    std::cout << "Sent " << bytes_sent << " bytes to client." << std::endl;
  }
  close(client_fd);
  close(server_fd);
  return 0;
}
