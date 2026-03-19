#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct DNS_HEADER {
    unsigned short id;  // unique identifier for each query
    unsigned short flags; //contains multiple flags
    unsigned short qdcount; //no of questions
    unsigned short anscount; // no of ans records
    unsigned short nscount; //number of authority records
    unsigned short arcount;  // number of additional records
};

struct QUESTION {
    unsigned short qtype;
    unsigned short qclass;
};

void encode_input(unsigned char *dst, char *src) {
    int j = 0, start = 0;
    int len = strlen(src);

    for(int i = 0; i <= len ;i++) {
        if(src[i] == '.' || src[i] == '\0') {
            dst[j++] = i - start;
            for(int k = start; k < i; k++) {
                dst[j++] = src[k];
            }
            start = i + 1;
        }
    }
    dst[j] = 0;
}

int main() {
    unsigned char buffer[512];
    memset(buffer, 0 , sizeof(buffer));

    struct DNS_HEADER *dns = (struct DNS_HEADER*)buffer;
    dns->id = htons(7564); // random number but you should set this to a new random number for every request
    dns-> flags = htons(0x0100);
    dns->qdcount = htons(1); //one question
    dns->anscount = 0;
    dns->nscount = 0;
    dns->arcount = 0;

    unsigned char *qname = buffer + sizeof(struct DNS_HEADER);
    char *domain = "www.google.com";
    encode_input(qname,domain);

    struct QUESTION *qinfo = (struct QUESTION *)(qname + strlen((char *)qname) + 1);
    qinfo->qclass = htons(1); //IN  (internet)
    qinfo->qtype = htons(1); // A record
    
    int pkt_len = sizeof(struct DNS_HEADER) + strlen((char*)qname) + 1 + sizeof(struct QUESTION);
    printf("\n");
    return 0;
}
