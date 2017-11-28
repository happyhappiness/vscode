int
main(int argc, char *argv[])
{
#define PACKET_BUFSZ        1024
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
        return 1;
    }

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argv[var][0] == '-') {
        if (argv[var][1] == '4')
            prefer = AF_INET;
        else if (argv[var][1] == '6')
            prefer = AF_INET6;
        else if (argv[var][1] == 'E')
            edns_max = atoi(argv[var++]);
        else {
            fprintf(stderr, "usage: %s [-6|-4] [-E packet-size] ip port\n", argv[0]);
            fprintf(stderr, "  EDNS packets my be up to %d\n", PACKET_BUFSZ);
            return 1;
        }

        var++;
    }

    s = socket(PF_INET, SOCK_DGRAM, 0);

    if (s < 0) {
        perror("socket");
        return 1;
    }

    memset(&S, '\0', sizeof(S));

    if (prefer == 6) {
        S = (struct sockaddr *) new sockaddr_in6;
        memset(S,0,sizeof(struct sockaddr_in6));

        ((struct sockaddr_in6 *)S)->sin6_family = AF_INET6;
        ((struct sockaddr_in6 *)S)->sin6_port = htons(atoi(argv[var+1]));

        if ( ! inet_pton(AF_INET6, argv[var], &((struct sockaddr_in6 *)S)->sin6_addr.s_addr) ) {
            perror("listen address");
            return 1;
        }

        s = socket(PF_INET6, SOCK_DGRAM, 0);
    } else {
        S = (struct sockaddr *) new sockaddr_in;
        memset(S,0,sizeof(struct sockaddr_in));

        ((struct sockaddr_in *)S)->sin_family = AF_INET;
        ((struct sockaddr_in *)S)->sin_port = htons(atoi(argv[var+1]));

        if ( ! inet_pton(AF_INET, argv[var], &((struct sockaddr_in *)S)->sin_addr.s_addr) )
            perror("listen address");
        return 1;
    }
}