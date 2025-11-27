Command:
compile --
gcc "/mnt/d/c program/CNT/udp_server.c" -o "/mnt/d/c program/CNT/udp_server"
gcc "/mnt/d/c program/CNT/udp_client.c" -o "/mnt/d/c program/CNT/udp_client"

run--
"/mnt/d/c program/CNT/udp_server"
"/mnt/d/c program/CNT/udp_client"

✅ THEORY – UDP SERVER (Trig Calculator Server)
📌 What the UDP Server does

Creates a UDP socket on port 8080.

Continuously waits for messages sent by any UDP client.

Accepts two types of input:

"Hello" → replies with "Hello from server!"

Trigonometric commands → for example:

sin 30

cos 60

tan 45

Converts the given angle from degrees to radians and applies the appropriate function (sin, cos, tan) from <math.h>.

Sends the calculated numeric value back to the client as a string.

If input format or command is incorrect, sends an error message (e.g., "Invalid format" or "Unknown command").

📌 Important Concepts and Functions Used (Server)

UDP Socket

socket(AF_INET, SOCK_DGRAM, 0)


AF_INET → IPv4 addressing

SOCK_DGRAM → UDP protocol (connectionless, packet-based)

Server Address Setup

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);


Binds to any local IP on port 8080.

bind()

Associates the socket with the given IP + port.

Tells the OS that this process will receive incoming UDP packets on port 8080.

recvfrom()

Receives one complete UDP datagram from a client.

Stores:

Data in buffer

Client’s address in cliaddr

Works without a connection (UDP is connectionless).

sendto()

Sends a UDP datagram to the specific client whose address was stored in cliaddr.

Trigonometric Calculations

UDP server uses:

sin(), cos(), tan()  from <math.h>


Since these functions use radians, the server converts input degrees using:

radians = degrees × (π / 180)


Parsing User Input

sscanf(buffer, "%s %lf", cmd, &value)


Splits "sin 30" into:

cmd = "sin"

value = 30.0

✅ THEORY – UDP CLIENT (Trig Calculator Client)
📌 What the UDP Client does

Creates a UDP socket.

Sets the server address to:

IPv4

Port 8080

Local machine (same computer)

Sends an initial "Hello" to the UDP server.

Receives and prints the server's "Hello from server!" response.

Enters a loop where it:

Asks the user to input a trig command (e.g., "sin 30", "cos 60", "tan 45")

Sends the user command to the UDP server

Waits for and prints the server response

If the user types "end", the loop stops and the socket is closed.

📌 Important Concepts and Functions Used (Client)

UDP Socket

socket(AF_INET, SOCK_DGRAM, 0)


Same properties as server (IPv4 + UDP datagram).

Server Address

servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr = INADDR_ANY;


Since client and server run on the same machine in lab experiments.

sendto()

Sends UDP messages to the server, including:

Initial "Hello"

User trig commands ("sin 30" etc.)

recvfrom()

Receives replies from the server:

"Hello from server!"

Trigonometric result

Error messages

User Input Loop

fgets() takes input from keyboard.

strcasecmp(buffer, "end") detects exit command.

Every non-exit input gets sent to the server for processing.

