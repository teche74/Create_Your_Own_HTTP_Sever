-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                                        NN   NN    EEEEEEE    TTTTTTT    W     W    OOOOO    RRRRRR     K    K        
                                                                        NNN  NN    EE           TTT      W  W  W   O     O   R     R    K   K         
                                                                        NNNN NN    EEEE         TTT      W  W  W   O     O   RRRRRR     K  K          
                                                                        NN NNNN    EE           TTT      W W W W   O     O   R   R      K   K         
                                                                        NN  NNN    EEEEEEE      TTT       W   W     OOOOO    R    R     K    K      

                                                                        PPPPPP    RRRRRR     OOOOO     GGGGG    RRRRRR    AAAAA    MMM   MMM  MMM   MMM    IIIIIIII   N     N    GGGGG
                                                                        P     P   R     R   O     O   G         R    R   A     A   M  M M  M  M  M M  M       II      NN    N    G
                                                                        PPPPPP    RRRRRR    O     O   G GGGGG   RRRRRR   AAAAAAA   M   M   M  M   M   M       II      N N   N    G GGGGG
                                                                        P         R   R     O     O   G     G   R   R    A     A   M       M  M       M       II      N  N  N    G     G
                                                                        P         R    R     OOOOO     GGGGG    R    R   A     A   M       M  M       M    IIIIIIII   N   N N    GGGGG

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

## LIBRARIES AND THEIR NEED

![image](https://github.com/teche74/Create_Your_Own_HTTP_Sever/blob/main/images/Screenshot%202024-03-29%20112358.png)

## Workflow

```bash
1 : "Welcome to our TCP networking journey! We have our Server, the Network, and the Client." ( INTODUCING COMPONENTS )

    _    ___________________________________________________      _
   / \                                                           / \
  |   |            _______    ___________    _______            |   |
  |___|           /       \  /           \  /       \           |___|
   | |           |  Server | |   Network  | | Client |           | |
   | |            \_______/  \___________/  \_______/            | |
   | |___________________________________________________________| |
   |_______________________________________________________________|


2: "Let's start by setting up our Server." (SETTING UP SERVER)

    _    ___________________________________________________      _
   / \                                                           / \
  |   |            _______    ___________    _______            |   |
  |___|           /       \  /           \  /       \           |___|
   | |           |    🛠️   ||            | |        |           | |
   | |            \_______/  \___________/  \_______/           | |
   | |__________________________________________________________| |
   |______________________________________________________________|

3: "Next, let's prepare our Network for incoming connections." (PREPARING NETWORK)

    _    ___________________________________________________      _
   / \                                                           / \
  |   |            _______    ___________    _______            |   |
  |___|           /       \  /           \  /       \           |___|
   | |           |         | |    🌐     | |        |            | |
   | |            \_______/  \___________/  \_______/            | |
   | |__________________________________________________________ | |
   |_______________________________________________________________|


4:  "Ah, here comes our Client. Let's welcome them." (WELCOMING CLIENT)

    _    ___________________________________________________     _
   / \                                                          / \
  |   |            _______    ___________    _______           |   |
  |___|           /       \  /           \  /       \          |___|
   | |           |         | |           | |   👋   |          | |
   | |            \_______/  \___________/  \_______/           | |
   | |__________________________________________________________| |
   |______________________________________________________________|


5 : "Time to accept the connection and establish communication." (ACCEPT CONNECTION)

    _    ___________________________________________________     _
   / \                                                          / \
  |   |            _______    ___________    _______           |   |
  |___|           /       \  /           \  /       \          |___|
   | |           |         | |            ||   🤝   |          | |
   | |            \_______/  \___________/  \_______/           | |
   | |__________________________________________________________| |
   |______________________________________________________________|

6 : "Let's exchange messages with our Client." (EXCHANGE MESSAGES)

    _    ___________________________________________________     _
   / \                                                          / \
  |   |            _______    ___________    _______           |   |
  |___|           /       \  /           \  /       \          |___|
   | |           |         | |            ||   📨   |    📨    | |
   | |            \_______/  \___________/  \_______/           | |
   | |__________________________________________________________| |
   |______________________________________________________________|

7 :  "That's it for our TCP communication. Time to wrap things up." (END COF COMMUNICATION / WRAPPING UP)

    _    ___________________________________________________     _
   / \                                                          / \
  |   |            _______    ___________    _______           |   |
  |___|           /       \  /           \  /       \          |___|
   | |           |         | |           | |         |          | |
   | |            \_______/  \___________/  \_______/           | |
   | |__________________________________________________________| |
   |______________________________________________________________|

```


## SOCKET INITIALIZATION

```bash
                 /$$$$$$                                  /$$      
              /$$__  $$                                | $$      
  /$$$$$$    | $$  \__/  /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$    
 /$$__  $$   |  $$$$$$  /$$__  $$|  $$ /$$/ /$$__  $$|_  $$_/    
| $$  \ $$    \____  $$| $$  \ $$ \  $$$$/ | $$  \ $$  | $$      
| $$  | $$    /$$$$$$$| $$  | $$  >$$  $$ | $$  | $$  | $$ /$$  
| $$$$$$$/   /$$__  $$|  $$$$$$/ /$$/\  $$|  $$$$$$/  |  $$$$/  
| $$____/   |  $$$$$$/ \______/ | $$  \ $$ \______/    \___/    
| $$        \______/            |  $$$$$$/                      
| $$                             \______/                       
|__/                                                             

```

- We use `socket()` from sys/socket.h

```cpp
  int socket(int domain, int type, int protocol);

domain: Specifies the communication domain in which the socket should be created.
      - AF_INET for IPv4 communication.
      - AF_INET6 for IPv6 communication.

type: Specifies the type of socket to be created.
      - SOCK_STREAM for TCP sockets
      - SOCK_DGRAM for UDP sockets.

protocol: Specifies a particular protocol to be used with the socket.
  - '0' to indicate that the system should choose the appropriate protocol based on the specified domain and type.

int server_fd = socket(AF_INET, SOCK_STREAM, 0); // 'server_fd' typically refers to the socket file descriptor associated with the server.
```

```bash

  _________________
 /                 \        |-----------> return +ve value on succesful socket instatntiation.
|    SOCKET CREATED| --- >  |
 \_________________/        |-----------> retruns -ve value on socket instantiation failure. 

```

## SETTING UP RESUSE PORT FUNCTIONALITY FOR FASTER SERVER RESTART

```CPP
// Enable functionality to reuse the port
int reuse = 1;
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return 1;
}
```
- `When a server process is restarted, it often needs to bind to the same port it was using before. Without SO_REUSEPORT, the operating system typically waits for a timeout period (known as the TIME_WAIT state) before allowing the port to be reused. This prevents a new socket from binding to the port immediately.
With SO_REUSEPORT, the port can be reused immediately, allowing the server to restart more quickly.`

## DEFINING SERVER ADDRESS STRUCTURE

```CPP
  struct sockaddr_in server_addr;   //sockaddr_in is a structure used to specify a socket address for IPv4 communication. Here, server_addr is an instance of this structure, which will hold the server's address information.
```

## SETTING ADDRESS FAMILY AND PORT

```CPP
server_addr.sin_family = AF_INET;  // sin_family is set to AF_INET, indicating IPv4 communication. 
server_addr.sin_addr.s_addr = INADDR_ANY;  // sin_addr.s_addr is set to INADDR_ANY, allowing the socket to accept connections on any available network interface.
server_addr.sin_port = htons(4221);  // sin_port is set to 4221, specifying the port number to bind to. The port number is converted to network byte order using htons().
```

## BINDING THE SOCKET

```CPP
if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 4221\n";
    return 1;
}

```

## DEFINING PENDING CONNECTIONS LENGTH

```CPP
int connection_backlog = 5; // It determines how many incoming connections can wait in the queue before the server starts rejecting new connections.
```

## LISTENING INCOMING CONNECTION

```CPP
if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
}
```


## PREPARING CLIENT ADDRESS STRUCTURE

```CPP
struct sockaddr_in client_addr; // structure that will hold the address information of the client once a connection is accepted.
socklen_t client_addr_len = sizeof(client_addr); // is the size of the client_addr structure. It's initially set to the size of the structure.
```


## ACCEPTING CLIENT CONNECTION 

```CPP
int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len);
```

- `Accept()` function blocks the execution until a client connection is established.
- It accepts the incoming connection on the server_fd socket and creates a new socket client_fd for communication with the client.
- The address information of the client is stored in the client_addr structure, and the actual size of the client address structure is updated to client_addr_len.



## CLOSING SOCKETS

```CPP
close(server_fd);
close(client_fd);
```
- Once the connection is accepted and the client communication is done, the server socket (server_fd) and the client socket (client_fd) are closed to release resources.
