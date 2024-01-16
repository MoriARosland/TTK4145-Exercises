// #include <stdio.h>
// #include <winsock2.h>

// int main() {
//   printf("Hello.");

//   return 0;
// }

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
//
#include <windows.h> // Include for Sleep function

int main(void) {
  WSADATA wsaData;
  SOCKET socket_desc;
  struct sockaddr_in server_addr, client_addr;
  char server_message[2000], client_message[2000];
  int client_struct_length = sizeof(client_addr);

  // Initialize Winsock:
  int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (wsaStartupResult != 0) {
    printf("WSAStartup failed with error: %d\n", wsaStartupResult);
    return -1;
  }

  // Clean buffers:
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));

  // Create UDP socket:
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

  // Bind to the set port and IP:
  if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
    printf("Couldn't bind to the port: %d\n", WSAGetLastError());
    closesocket(socket_desc);
    WSACleanup();
    return -1;
  }
  printf("Done with binding\n");

  printf("Listening for incoming messages...\n\n");

  // Receive client's message:
  if (recvfrom(socket_desc, client_message, sizeof(client_message), 0,
               (struct sockaddr *)&client_addr, &client_struct_length) == SOCKET_ERROR) {
    printf("Couldn't receive: %d\n", WSAGetLastError());
    closesocket(socket_desc);
    WSACleanup();
    return -1;
  }
  printf("Received message from IP: %s and port: %i\n",
         inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

  printf("Msg from client: %s\n", client_message);

  // Respond to client:
  strcpy(server_message, client_message);

  if (sendto(socket_desc, server_message, strlen(server_message), 0,
             (struct sockaddr *)&client_addr, client_struct_length) == SOCKET_ERROR) {
    printf("Can't send: %d\n", WSAGetLastError());
    closesocket(socket_desc);
    WSACleanup();
    return -1;
  }

  while (1) {
    Sleep(10000);
  }

  // Close the socket:
  closesocket(socket_desc);
  WSACleanup();

  return 0;
}
