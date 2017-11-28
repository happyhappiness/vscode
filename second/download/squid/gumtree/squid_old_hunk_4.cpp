    unsigned short s = htons(qid);
    memcpy(buf, &s, sizeof(s));
}

#if DRIVER
#include <sys/socket.h>
#include <sys/time.h>
int
main(int argc, char *argv[])
{
    char input[512];
    char buf[512];
    char rbuf[512];
    size_t sz = 512;
    unsigned short sid;
    int s;
    int rl;
    struct sockaddr_in S;
    if (3 != argc) {
        fprintf(stderr, "usage: %s ip port\n", argv[0]);
