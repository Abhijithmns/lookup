#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>



int main() {

    printf("Performing DNS lookup....\n");

    //DNS lookup logic

    char ipstr[INET6_ADDRSTRLEN];
    struct addrinfo *result;
    const char *node = "google.com";
    const char *service = "http";
   struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = 0; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    int res = getaddrinfo(node,service,&hints,&result);
    // ignoring the value of res for now
    (void)res;

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
