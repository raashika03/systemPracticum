#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 512

int main()
{
    
    char filename1[BUF_SIZE];
    printf("Enter the filename:\n");
    scanf("%s",&filename1);
    
    char filename[BUF_SIZE] ="Saved-";
    strcat(filename,filename1);
    
    /*Create file where data will be stored */
    FILE *fp = fopen(filename, "ab");
    if(NULL == fp)
    {
        printf("Error! creating file %s \n", filename);
        return 1;
    }

    /*Create a socket*/
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\nError! creating socket \n");
        return 1;
    }

    printf("Client socket created successfully.\n");

    /* Initialize sockaddr_in data structure */
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*Trying to connet with server*/
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\nError! Connection Failed! \n");
        return 1;
    }

    printf("Connection established successfully!\n");

    /* Receive data in chunks of BUF_SIZE bytes */
    int sofar = 0;
    int bytesReceived = 0;
    char buff[BUF_SIZE];
    memset(buff, '0', sizeof(buff));
    
    write(sockfd, filename1, sizeof(buff));
    printf("Downloading %s from server & saving as %s in client machine \n",filename1, filename);
    while((bytesReceived = read(sockfd, buff, BUF_SIZE)) > 0)
    {
        sofar+=bytesReceived;
        printf("~");
        fwrite(buff, 1,bytesReceived,fp);
    }
    printf("\nDownloaded %d bytes \n", sofar);

    if(bytesReceived < 0)
        printf("\nError Reading!\n");
    
    return 0;
}




