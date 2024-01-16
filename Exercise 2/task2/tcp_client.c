#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

#define PORT 8080

int main() {
  WSADATA wsaData;
  SOCKET sock;
  struct sockaddr_in serverAddr;

  // Initialize Winsock
  WSAStartup(MAKEWORD(2, 2), &wsaData);

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);

  // Setup the server address
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Connect to the server
  connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  // Communication code here (send/recv)
  char message[] = "Hei studass :)";
  char buffer[1024];
  int receivedBytes;

  // Send a message to the server
  send(sock, message, strlen(message), 0);

  // Receive a response from the server
  receivedBytes = recv(sock, buffer, sizeof(buffer), 0);
  if (receivedBytes > 0) {
    buffer[receivedBytes] = '\0'; // Null-terminate the received data
    printf("Response from server: %s\n", buffer);
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
  closesocket(sock);
  WSACleanup();
  return 0;
}