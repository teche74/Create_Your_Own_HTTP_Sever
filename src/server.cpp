#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<regex>

const std::string SERVER_200_OK = "HTTP/1.1 200 OK\r\n\r\n";
const std::string RESPONSE_404 = "HTTP/1.1 404 Not Found\r\n\r\n";

int main(int argc, char **argv)
{
  // You can use print statements as follows for debugging, they'll be visible when running tests.
  std::cout << "Logs from your program will appear here!\n";

  // Uncomment this block to pass the first stage
  //
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0)
  {
    std::cerr << "Failed to create server socket\n";
    return 1;
  }
  //
  // // Since the tester restarts your program quite often, setting REUSE_PORT
  // // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(4221);
  
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
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
  
  int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *)&client_addr_len);
  std::cout << "Client connected\n";

  char buff[1024];

  int bytesRecieved = recv(client_fd,buff,1024, 0);

  if(bytesRecieved < 0){
    std::cout<< "error in receiving";
    return 2; 
  }

  const std::string request(buff,1024);
  std::cout<< request;

  std::regex reg("^GET [\\/a-zA-Z\\.]+ HTTP\\/1\\.1\\r\n");
  std::smatch sm;

  bool send200 = regex_search(request,sm,reg);

  int sendResponse = -1;

  if(send200)
    sendResponse = send(client_fd,SERVER_200_OK.c_str(),SERVER_200_OK.size(),0);
  else
    sendResponse = send(client_fd,RESPONSE_404.c_str(),RESPONSE_404.size(),0);

  if(sendResponse < 0){
    std::cout<<"issue with send";
    return 3;
  }
  
  close(server_fd);

  return 0;
}
