#include <stdio.h>
#include <string.h>
#include <winsock2.h>

int main(void) {
  WSADATA wsaData;
  SOCKET socket_desc;
  struct sockaddr_in server_addr;
  char server_message[2000], client_message[2000];
  int server_struct_length = sizeof(server_addr);

  // Initialize Winsock:
  int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (wsaStartupResult != 0) {
    printf("WSAStartup failed with error: %d\n", wsaStartupResult);
    return -1;
  }

  // Clean buffers:
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));

  // Create socket:
  socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (socket_desc == INVALID_SOCKET) {
    printf("Error while creating socket: %d\n", WSAGetLastError());
    WSACleanup();
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(2000);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Get input from the user:
  printf("Enter message: ");
  fgets(client_message, sizeof(client_message), stdin);

  // Remove newline character, if present
  size_t len = strlen(client_message);
  if (len > 0 && client_message[len - 1] == '\n') {
    client_message[len - 1] = '\0';
  }

  // Send the message to server:
  if (sendto(socket_desc, client_message, strlen(client_message), 0,
             (struct sockaddr *)&server_addr, server_struct_length) < 0) {
    printf("Unable to send message\n");
    closesocket(socket_desc);
    WSACleanup();
    return -1;
  }

  // Receive the server's response:
  if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,
               (struct sockaddr *)&server_addr, &server_struct_length) < 0) {
    printf("Error while receiving server's msg\n");
    closesocket(socket_desc);
    WSACleanup();
    return -1;
  }

  printf("Server's response: %s\n", server_message);

  while (1) {

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Check if user wants to exit
    if (strcmp(client_message, "exit") == 0) {
      break;
    }
  }

  // Close the socket:
  closesocket(socket_desc);
  WSACleanup();

  return 0;
}
