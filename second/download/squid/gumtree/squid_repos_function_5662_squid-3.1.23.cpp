int
main(int argc, char *argv[])
{
    char input[512];
    char buf[512];
    char rbuf[512];
    size_t sz = 512;
    unsigned short sid, sidb;
    int s;
    int rl;

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
        else {
            fprintf(stderr, "usage: %s [-6|-4] ip port\n", argv[0]);
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

        if ( ! xinet_pton(AF_INET6, argv[var], &((struct sockaddr_in6 *)S)->sin6_addr.s_addr) )
            perror("listen address");
        return 1;
    }

    s = socket(PF_INET6, SOCK_DGRAM, 0);
}