/*
    We had to accept a TCP connection , read the data from connection . Respond with HTTP/1.1 200 OK\r\n\r\n 
       - HTTP/1.1 200 OK is the HTTP Status Line.
       - \r\n, also known as CRLF, is the end-of-line marker that HTTP uses.
       - The first \r\n signifies the end of the status line.
       - The second \r\n signifies the end of the response headers section (which is empty in this case).

                                           -%%%%%%%%%%%##**++==---::....                                     
                                  *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%##*+=--::...              
                                  #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%#*######******##*****+           
                                 .#@%**+++**##%%@@@@@@@@@@@@@@@@@@%#*#*******************:          
                                 .#@#*+.-*######%%%%#**+++++=+#@@%%#*#####***************+          
                                 .#@#*=:=***####%%%%%%%%%%%%%#%@@%##*####*****************:         
                                 .%@#*--+****######%%%%%%%%%%%@@@%##*#####***************+:         
                                 :%@##-=+****########%%%%%%%%%@@@%##*####****************+.         
                                 :%@#*-===+++**########%%%%%%@@@@%#**#####**************+*.         
                                 :@@#*-====++++**###########%%@@@%#*######**************+*          
                                 -@@#*--====+++++++*****#####%@@@%#*#######*************++          
                                 -@@#*--======++++++++++*****#@@%%#*#####***************++          
                                 -@%#*--========+++++++++++++#@@%%#*######**************++          
                                 =@%#*--=================+===#@@%%#*##*****************++=          
                                 =@%#*---====================#@@%#**#####*#************++=          
                                 =@%#*----===================%@@%#*########************++-          
                                 +@%%@#*+====================@@@%#*######*************+++-          
                                 +@@@@@@@@@%%*==============-@@@%#*###*#**************+++:          
                                 +@@@@@@@@@@@@@@@@@@@#+======@@@%#**##****************+++:          
                                 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%***#****************++++.          
                                 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%********************++++.          
                                 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%*******************+++++           
                                 *@@@@@@@@@@@@@##@@@@@@@@@@@@@@%#******************+++++=           
                                 #@%%@@@@@@@@@@@@@%#-:=*#%%@@@@%#*****************++++++=           
                                .#@@@@@@@@@@@@@@@@@@@@@%=::*@@@%#*****************++++++=           
                                 +##%%@@@@@@@@@@@@@@@@@@@@@@@@@%*****************++++++=-           
                    .*%#*#%##:     .:+####%%%@@@@@@@@@@@@@@@@@@%*****************+++=+==-           
                .:*@%##+**++%%#%%*-:.-++===**##%%%@@@@@@@@@@@@@%***************+++=+=+==:           
              -*%%%##%*#+*****+#**##%%%#*=======++*##%%%%@@@@@%#************++*++++++-.             
           -%@@#%#**+#+##+**=#*+#*+#+##+#%@@#+=========+####%%##*********+++++++++:.                
       .=%@@@@##*+*#+##*+#+##***+**+**+#*+#**#%%@#++======-==+*=--=****++*+**+=:                 .:.
     .*@@@@@@@%*##*###**+#***#+*#**#*+#***#=*+*#**%%%%#*+=====::++*****+***-:                    :. 
      +%@@@@@@@@@@########**#+#*+**+#*+*#*+#*+##+**+####%@@@#====++*****:                       ::  
       -*##%@@@@@@@@@%########*+#+*#*+*#+#*****=#*+*#****%@@@@@@#-=+=:                         :-   
         .:=*#%%@@@@@@@@@@%#########+*+##*+**+###******%@@@@@@%#*:......                      ::    
              .*##%%@@@@@@@@@@%###*+####+*%%####****#@@@@@@@##**=--=-==++++.               .-=.     
                 .-+#%%@@@@@@@@@@@%###*+##*=+##***%@@@@@@%#**+-.:..   ..:-==:         .:--:.        
                     .-*#%%@@@@@@@@@@@%##**%%%%%@@@@@@@%#**+: .:=#**==-+---:.:----::::.             
                         :+##%%@@@@@@@@@@@@@@@@@@@@@@##**+-. :#@#####***+--=.                       
                            .-+#%%%@@@@@@@@@@@@@@@%#**+-. .+@@@@@@@@%%%@@@%-                        
                                .:*##%%@@@@@@@@@%#**+: .=%@@@@@@@@@@@@@@##*=                        
                                    .-*##%%@@@#**+=. .*@@@@@@@@@@@@@@%#*****.                       
                                        :=*##**+-.   =@@@@@@@@@@@@@%#****+-.                        
                                           .::.      +@@@@@@@@@@@#****+-.                           
                                                      :+#%@@@@@#***+=.                              

*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
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

    std::string response = "HTTP/1.1 200 OK\r\n\r\n";
    sendData(client_fd, response);

    closeSocket(client_fd);
    closeSocket(server_fd);

    return 0;
}
