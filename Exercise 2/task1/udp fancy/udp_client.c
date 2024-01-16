#include <stdio.h>
#include <string.h>
#include <winsock2.h>

typedef struct {
  SOCKET socket_desc;
  struct sockaddr_in server_addr;
} UdpSender;

// Function to initialize the UDP sender
int init_udp_sender(UdpSender *sender, const char *ip, int port) {
  WSADATA wsaData;

  // Initialize Winsock
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    printf("WSAStartup failed\n");
    return 1;
  }

  // Create a socket
  sender->socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sender->socket_desc == INVALID_SOCKET) {
    printf("Could not create socket : %d\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  // Prepare the sockaddr_in structure
  sender->server_addr.sin_family = AF_INET;
  sender->server_addr.sin_addr.s_addr = inet_addr(ip);
  sender->server_addr.sin_port = htons(port);

  return 0;
}

// Function to send a message
int udp_send(UdpSender *sender, const char *message) {
  if (sendto(sender->socket_desc, message, strlen(message), 0,
             (struct sockaddr *)&(sender->server_addr), sizeof(sender->server_addr)) < 0) {
    printf("Send failed : %d\n", WSAGetLastError());
    return 1;
  }
  return 0;
}

// Function to clean up
void close_udp_sender(UdpSender *sender) {
  closesocket(sender->socket_desc);
  WSACleanup();
}

int main() {

  UdpSender sender;

  if (init_udp_sender(&sender, "127.0.0.1", 8888) != 0) {
    printf("Failed to initialize UDP sender \n");
  }

  udp_send(&sender, "Hello, UDP Server!");
  printf("UDP sendt a message.\n");

  char userInput[512];

  while (1) {
    memset(userInput, '\0', sizeof(userInput));

    // Get input from the user:
    printf("Enter message (type 'exit' to quit): ");
    fgets(userInput, sizeof(userInput), stdin);

    // Remove newline character, if present
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
      userInput[len - 1] = '\0';
    }

    // Check if user wants to exit
    if (strcmp(userInput, "exit") == 0) {
      break;
    }
  }

  close_udp_sender(&sender);

  return 0;
}