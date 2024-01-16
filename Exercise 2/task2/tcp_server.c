#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

#define PORT 8080

int main() {
  WSADATA wsaData;
  SOCKET serverSocket, clientSocket;
  struct sockaddr_in serverAddr, clientAddr;
  int clientAddrSize = sizeof(clientAddr);

  // Initialize Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Create socket
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  // Prepare the sockaddr_in structure
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  // Bind
  bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  // Listen
  listen(serverSocket, 3);

  // Accept incoming connection
  clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);
  printf("Connected to client.");

  // Communication code (send/recv)
  char buffer[1024];
  int receivedBytes;

  // Receive a message from the client
  receivedBytes = recv(clientSocket, buffer, sizeof(buffer), 0);
  if (receivedBytes > 0) {
    printf("Message received from client: %s\n", buffer);

    // Process the message (e.g., convert to uppercase)
    for (int i = 0; i < receivedBytes; i++) {
      buffer[i] = toupper(buffer[i]);
    }

    // Send a response back to the client
    send(clientSocket, buffer, receivedBytes, 0);
  }

  char exit[100];
  while (1) {
    printf("Enter a string (type 'exit' to quit): ");
    fgets(exit, sizeof(exit), stdin);
    if (strncmp(exit, "exit\n", 5) == 0) {
      break;
    }
    printf("You entered: %s", exit);
  }

  // Cleanup
  closesocket(clientSocket);
  closesocket(serverSocket);
  WSACleanup();
  return 0;
}