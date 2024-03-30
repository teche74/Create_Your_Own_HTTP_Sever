// Our task is to start a TCP server on port 4221

/*
  Socket Creation: Creates a socket file descriptor using the socket function.

  Set Socket Option: Sets the SO_REUSEPORT option to allow reuse of the port.

  Binding: Binds the socket to an address and port specified in the server_addr structure.

  Listening: Sets the socket to listen for incoming connections with a specified backlog.

  Accepting Connections: Blocks and waits for incoming connections. When a client connects, it accepts the connection and returns a new socket file descriptor (client_fd). The client's address information is stored in client_addr.

  Closing Server Socket: Closes the server socket (server_fd) since it's no longer needed for accepting connections.

  Handling Client Connection: This part would typically involve handling the client connection, such as receiving and sending data. However, this is not implemented in this example.

  Closing Client Socket: Closes the client socket (client_fd) after handling the connection.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
  iostream: The standard input/output stream library .

  cstdlib: This header provides general-purpose functions in the C programming language. It includes functions like atoi for converting strings to integers and malloc for memory allocation.

  string: This header provides the std::string class and related functions for handling strings in C++. It allows you to manipulate strings more easily than using C-style character arrays.

  cstring: It provides functions for manipulating C-style character arrays (strings).

  unistd.h: This header provides access to various POSIX operating system API functions. It includes functions like close, fork, read, and write, as well as constants like STDIN_FILENO and STDOUT_FILENO.

  sys/types.h: This header defines various data types used in system programming, such as pid_t for process IDs and size_t for sizes of objects.
  
  sys/socket.h: This header provides access to socket-related functions and data structures for network communication. Functions like socket, bind, listen, and accept are included in this header.

  arpa/inet.h: This header provides functions for handling IP addresses in network byte order and for converting between different formats. Functions like inet_pton and inet_ntop are included in this header.

  netdb.h: This header provides access to functions and data structures for domain name resolution (DNS) and network-related information. Functions like getaddrinfo and getnameinfo are included in this header.
*/
constexpr int SERVER_PORT = 4221;
constexpr int CONNECTION_BACKLOG = 5;


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

int waitForClientConnection(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    std::cout << "Waiting for a client to connect...\n";
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        std::cerr << "Failed to accept connection\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Client connected\n";
    return client_fd;
}

void closeSocket(int sockfd) {
    close(sockfd);
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

    int client_fd = waitForClientConnection(server_fd);
    
    closeSocket(client_fd);
    closeSocket(server_fd);

    return 0;
}
