# Simple C++ HTTP Server

This project is a simple HTTP server implemented in C++. It provides basic functionality to handle GET and POST requests, serve static files, and echo request content. The server is designed to be lightweight and easy to understand, making it suitable for learning purposes or small-scale projects.

## Features

- **GET Requests**: Handles GET requests to serve static files or echo request content.
- **POST Requests**: Supports POST requests to create new files on the server.
- **Static File Serving**: Serves static files from a specified directory.
- **Error Handling**: Provides basic error handling for invalid requests or server errors.
- **Multithreading**: Utilizes multithreading to handle multiple client connections concurrently.

## Dependencies
- C++ Compiler (e.g., g++)
- iostream: Standard input/output stream library.
- string: String manipulation library.
- cstring: C-style string manipulation library.
- fstream: File stream library for file input/output operations.
- map: Container that stores key-value pairs.
- thread: Multithreading support library.
- vector: Dynamic array container.
- unistd.h, sys/types.h, sys/socket.h, netdb.h: Networking and socket-related libraries.

# Trying Out the Simple C++ HTTP Server

To try out the Simple C++ HTTP Server, follow these steps:

## 1. Download the Code

Download or copy the provided C++ HTTP server code (Final Step ) into a file named `http_server.cpp`.

## 2. Compile the Code

Open a terminal and navigate to the directory where `http_server.cpp` is located. Then, compile the code using the following command:

```bash
   g++ -o http_server http_server.cpp -std=c++11 -pthread
```
## 3. Run the Server

Execute the generated executable file to start the HTTP server. Optionally, you can specify a directory from which to serve files using the `--directory` flag. Here's the command to run the server:

```bash
./http_server [--directory <directory_path>]
```
Replace <directory_path> with the path of the directory you want to serve files from. If you omit the --directory flag, the server will serve files from the current directory.

## 4. Accessing the Server
Once the server is running, you can access it using a web browser or an HTTP client. By default, the server listens on port 4221. Open a web browser and navigate to http://localhost:4221 to interact with the server.
