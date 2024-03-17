#include <iostream>
#include <cstdlib>
#include <thread>
#include <pthread.h>
#include <string>
#include <regex>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

void handleConnection(int clientSock)
{
  char buf[1024];
  int bytesReceived = recv(clientSock, buf, 1024,0);
  if (bytesReceived < 0)
  {
    std::cout << "error in recv";
    return;
  }


  const std::string request(buf, 1024);
  std::regex regDefault("^GET \\/ HTTP\\/1\\.1\\r\\n");
  std::regex regEcho("^GET \\/echo\\/([\\/a-zA-Z0-9\\.\\-]+) HTTP\\/1\\.1\\r\\n");
  std::regex regUserAgent("^GET \\/user\\-agent\\ HTTP\\/1\\.1\\r\\nHost\\: [a-zA-Z]+\\:[0-9]+\\r\\nUser\\-Agent\\: ([a-zA-Z0-9\\/\\.]+)");
  std::smatch smRequest;
  const std::string response200Ok = "HTTP/1.1 200 OK\r\n";
  const std::string response404 = "HTTP/1.1 404 Not Found\r\n";
  
  std::string response = "";
  if (regex_search(request, smRequest, regDefault))
  {
    response = response200Ok + "\r\n";
  }
  else if (regex_search(request, smRequest, regEcho))
  {
    const std::string echoString = smRequest.str(1);
    response = response200Ok;
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: " + std::to_string(echoString.length()) + "\r\n";
    response += "\r\n" + echoString + "\r\n";
  }
  else if (regex_search(request, smRequest, regUserAgent))
  {
    const std::string userAgent = smRequest.str(1);
    response = response200Ok;
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: " + std::to_string(userAgent.length()) + "\r\n";
    response += "\r\n" + userAgent + "\r\n";
  }
  else
    response = response404 + "\r\n";
  int sendResponse = send(clientSock, response.c_str(), response.length(),0);
  if (sendResponse < 0)
  {
    std::cout << "issue with send";

    return;
  }
  else
  {
    std::cout << "Sent:\n" + response;
  }
}


int main(int argc, char **argv) {
  /
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
   std::cerr << "Failed to create server socket\n";
   return 1;
  }
  //
  // Since the tester restarts your program quite often, setting REUSE_PORT
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }
  //
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(4221);
  //
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 4221\n";
    return 1;
  }
  //
  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }
  while (true)
  {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int clientSock = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
    if (clientSock != -1)
    {
      std::thread(handleConnection, clientSock).detach();
    }
  }
  
  close(server_fd);
  return 0;
}