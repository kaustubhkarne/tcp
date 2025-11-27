Command:
compile --
gcc "/mnt/d/c program/CNT/udp_server.c" -o "/mnt/d/c program/CNT/udp_server"
gcc "/mnt/d/c program/CNT/udp_client.c" -o "/mnt/d/c program/CNT/udp_client"

run--
"/mnt/d/c program/CNT/udp_server"
"/mnt/d/c program/CNT/udp_client"

THEORY – TCP SERVER (What it does + concepts)
What the TCP server does (overview)

Creates a TCP socket to listen for connections.

Binds that socket to a port number (8080).

Listens for incoming connection requests from clients.

Accepts a client connection and gets a new dedicated socket.

Sends a small greeting message to the client.

Opens a local file (send.txt) and sends its contents over the connection.

Closes the connection and terminates.

Important concepts in server

Socket
A socket is like a communication endpoint.
socket(AF_INET, SOCK_STREAM, 0) → create a TCP/IPv4 socket.

AF_INET
Address family for IPv4 (e.g., 127.0.0.1, 192.168.x.x).

SOCK_STREAM
Type of socket that uses TCP (reliable, connection-oriented, stream-based).

Bind
bind() attaches the socket to a local IP + port.
In your code you use INADDR_ANY, which means “any local IP on this machine”, and port 8080.

Listen
listen() marks the socket as a passive listening socket.
It does not accept connections by itself — it just tells the OS to queue connection requests.

Accept
accept() waits (blocks) until some client tries to connect.
When a client connects:

You get a new socket (e.g., new_socket) used to talk to that client.

The original server_fd stays in listening mode and could accept more clients (in more complex programs).

Send
send() writes bytes over the TCP connection.
You use it to send:

The greeting string "Hello from server!"

The contents of send.txt (chunk by chunk).

File I/O

fopen("...","rb") opens a file for reading in binary mode.

fread() reads a chunk of that file into buffer.

That buffer is then sent using send().

TCP behavior
TCP guarantees:

Reliable delivery (no silent loss; if something fails, the connection breaks).

In-order delivery (data arrives in the same order it was sent).

Stream-based (no inherent message boundaries; just a continuous byte stream).

📚 THEORY – TCP CLIENT (What it does + concepts)
What the TCP client does (overview)

Creates a TCP socket.

Fills the server address with:

IP = 127.0.0.1 (localhost – same machine)

Port = 8080

Uses connect() to establish a TCP connection to the server.

Once connected:

Receives the greeting message and prints it.

Opens a file received.txt locally.

Receives the file data sent by the server and writes it into received.txt.

Closes the file and socket.

Important concepts in client

Socket (again)
socket(AF_INET, SOCK_STREAM, 0) creates the client-side TCP socket.

Server address

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);


sin_family = address family (IPv4).

sin_port = port number in network byte order (TCP port 8080).

inet_pton converts the dotted string "127.0.0.1" into numeric format used by the OS.

Connect

connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));


This performs the TCP 3-way handshake with the server.

If it succeeds, you have a full duplex connection for two-way data transfer.

Recv

recv(sock, buffer, BUFFER_SIZE, 0);


Receives bytes from the server.

First call receives the greeting.

Later calls (inside the loop) receive raw file data.

When the server finishes and closes its side, recv() returns 0 → loop ends.

File writing

fp = fopen("received.txt", "wb");
fwrite(buffer, 1, bytesReceived, fp);


Data received from the server is written into a local file.

This is how the file is reconstructed at the client side.

Current working directory
received.txt is created in the directory from which you run the client, not necessarily where the source file is.