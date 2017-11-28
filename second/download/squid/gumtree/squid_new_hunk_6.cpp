    for (i = 15; i >= 0; i--, p+=4) {
        snprintf(p, 5, "%1x.%1x.", ((r[i])&0xf), (r[i]>>4)&0xf );
    }

    snprintf(p,10,"ip6.arpa.");

    return rfc3596BuildHostQuery(rev, buf, sz, qid, query, RFC1035_TYPE_PTR, edns_sz);
}


#if DRIVER

/* driver needs the rfc1035 code _without_ the main() */
#  define main(a,b) rfc1035_main(a,b)
#  include "rfc1035.c"
#  undef main(a,b)

#include <sys/socket.h>

int
main(int argc, char *argv[])
{
#define PACKET_BUFSZ		1024
    char input[PACKET_BUFSZ];
    char buf[PACKET_BUFSZ];
    char rbuf[PACKET_BUFSZ];
    size_t sz = PACKET_BUFSZ;
    unsigned short sid, sidb;
    int s;
    int rl;
    ssize_t edns_max = -1;

    struct sockaddr* S;
    int var = 1;

    if ( argc < 3 || argc > 4) {
        fprintf(stderr, "usage: %s [-6|-4] ip port\n", argv[0]);
