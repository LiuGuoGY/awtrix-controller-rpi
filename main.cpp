#include <wiringPi.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include "awtrix-conf.h"

void error(char const * msg) {
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  int sockfd = 0, portno = 0;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256] = "hahahahhaha\0", temp = 0;
  int n = 0;

  wiringPiSetup();
  // pinMode(0,OUTPUT);
  // printf("Hello World!Remote VSCode\n");
  // if (argc < 3) {
  //   fprintf(stderr,"usage %s hostname port\n", argv[0]);
  //   exit(0);
  // }
  portno = 41152; //7001
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("ERROR opening socket");
  server = gethostbyname("139.199.153.158"); //127.0.0.1
  if (server == NULL) {
    error("ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
    error("ERROR connecting");
  // bzero(buffer, 256);// reset to zero
  n = write(sockfd,buffer,strlen(buffer));
  if (n < 0) 
    error("ERROR writing to socket");
  printf("tap any key to close\n");
  scanf("%c", &temp);
  close(sockfd);

// while(1)
  // {
  //   digitalWrite(0,HIGH);delay(500);
  //   digitalWrite(0,LOW);delay(500);
  // }
  return 1;
}
