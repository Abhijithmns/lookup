#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>



int main(int argc,char *argv[]) {

    if(argc!=2) {
        printf("Usage: <hosname>\n");
        return -1;
    }

    printf("Performing DNS lookup for %s\n",argv[1]);

    //DNS lookup logic

    char ipstr[INET6_ADDRSTRLEN];
    struct addrinfo *result;
    const char *node = argv[1];
    const char *service = NULL;
   struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int res = getaddrinfo(node,service,&hints,&result);

    if (res != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(res));
        return -1;
    }

    // printing the results of DNS lookup
    struct addrinfo *rp;
    for(rp = result; rp!=NULL; rp = rp->ai_next){
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        if(rp->ai_family == AF_INET) {
            ipv4 = (struct sockaddr_in *)rp->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else {
            ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        //converting IP addresses to string and printing it
        inet_ntop(rp->ai_family,addr,ipstr,sizeof(ipstr));

        printf("%s: %s\n",ipver,ipstr);
    }

    freeaddrinfo(result);

    return 0;
}
