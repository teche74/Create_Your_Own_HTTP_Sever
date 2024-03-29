# Simple C++ HTTP Server

This project is a simple HTTP server implemented in C++. It provides basic functionality to handle GET and POST requests, serve static files, and echo request content. The server is designed to be lightweight and easy to understand, making it suitable for learning purposes or small-scale projects.

## Features

- **GET Requests**: Handles GET requests to serve static files or echo request content.
- **POST Requests**: Supports POST requests to create new files on the server.
- **Static File Serving**: Serves static files from a specified directory.
- **Error Handling**: Provides basic error handling for invalid requests or server errors.
- **Multithreading**: Utilizes multithreading to handle multiple client connections concurrently.

## Usage

1. **Compilation**: Compile the source code using a C++ compiler. Ensure that you have the necessary dependencies installed (see Dependencies section below).
   ```bash
   g++ -o http_server http_server.cpp -std=c++11 -pthread

2. **Execution**: Run the compiled executable to start the HTTP server. Optionally, you can specify a directory from which to serve files using the --directory flag.

  ```bash
  ./http_server [--directory <directory_path>]
  ```


3. **Accessing the Server**: Once the server is running, you can access it using a web browser or an HTTP client. By default, the server listens on port 4221.

4. **Testing**: Use your preferred web browser or an HTTP client (e.g., cURL, Postman) to send GET and POST requests to the server and observe the responses.

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

