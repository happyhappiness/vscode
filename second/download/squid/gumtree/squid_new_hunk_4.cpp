    unsigned short s = htons(qid);
    memcpy(buf, &s, sizeof(s));
}

#if DRIVER
#include <sys/socket.h>
int
main(int argc, char *argv[])
{
    char input[SQUID_DNS_BUFSZ];
    char buf[SQUID_DNS_BUFSZ];
    char rbuf[SQUID_DNS_BUFSZ];
    size_t sz = SQUID_DNS_BUFSZ;
    unsigned short sid;
    int s;
    int rl;
    struct sockaddr_in S;
    if (3 != argc) {
        fprintf(stderr, "usage: %s ip port\n", argv[0]);
