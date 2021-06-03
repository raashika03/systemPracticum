#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define PORT 8080
#define BUF_SIZE 512


int main()
{
    //TCP connection
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Socket generated successfully! \n");

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    if(listen(sockfd, 10) == -1)
    {
        printf("Error: Failed to listen! \n");
        return -1;
    }
    printf("Working sound: Listening to port! %d \n", PORT);

    for (;;)
    {
        int connfd = accept(sockfd, (struct sockaddr*)NULL ,NULL);
        printf("Connection Established! %d\n",connfd);

        printf("Connected with client! \n");
        pid_t childpid;
        if ((childpid = fork()) == 0) {
            
            char buf[BUF_SIZE]={0};
            read(connfd, buf, sizeof(buf));
            printf(" Transfering file %s\n",buf);
            
            char filename[BUF_SIZE];
            strcpy(filename,buf);
            
            /* Open the file which you want to transfer */
            FILE *fp = fopen(filename,"rb");
            if(fp==NULL)
            {
                printf("File open error!");
                return 1;
            }

            /* Read data from your file and send it to the client*/
            int sofar = 0;
            for (;;)
            {
                /* Read file in chunks of BUF_SIZE bytes */
                unsigned char buff[BUF_SIZE]={0};
                int nread = fread(buff,1,BUF_SIZE,fp);
                sofar += nread;
                printf("^");

                /* If read was success, then send data. */
                if(nread > 0)
                    write(connfd, buff, nread);

                if (nread < BUF_SIZE)
                {
                    if (feof(fp))
                        printf("\nEnd of file\nTransfered %d data", sofar);
                    if (ferror(fp))
                        printf("Error reading\n");
                    break;
                }
            }
        }
        printf("Connection Closed!");
        close(connfd);
    }
    return 0;
}

