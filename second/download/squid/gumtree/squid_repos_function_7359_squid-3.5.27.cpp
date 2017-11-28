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
        return 1;
    }
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket");
        return 1;
    }
    memset(&S, '\0', sizeof(S));
    S.sin_family = AF_INET;
    S.sin_port = htons(atoi(argv[2]));
    S.sin_addr.s_addr = inet_addr(argv[1]);
    while (fgets(input, RFC1035_DEFAULT_PACKET_SZ, stdin)) {
        struct in_addr junk;
        strtok(input, "\r\n");
        memset(buf, '\0', RFC1035_DEFAULT_PACKET_SZ);
        sz = RFC1035_DEFAULT_PACKET_SZ;
        if (inet_pton(AF_INET, input, &junk)) {
            sid = rfc1035BuildPTRQuery(junk, buf, &sz);
        } else {
            sid = rfc1035BuildAQuery(input, buf, &sz);
        }
        sendto(s, buf, sz, 0, (struct sockaddr *) &S, sizeof(S));
        do {
            fd_set R;
            struct timeval to;
            FD_ZERO(&R);
            FD_SET(s, &R);
            to.tv_sec = 10;
            to.tv_usec = 0;
            rl = select(s + 1, &R, NULL, NULL, &to);
        } while (0);
        if (rl < 1) {
            printf("TIMEOUT\n");
            continue;
        }
        memset(rbuf, '\0', RFC1035_DEFAULT_PACKET_SZ);
        rl = recv(s, rbuf, RFC1035_DEFAULT_PACKET_SZ, 0);
        {
            unsigned short rid = 0;
            int i;
            int n;
            rfc1035_rr *answers = NULL;
            n = rfc1035AnswersUnpack(rbuf,
                                     rl,
                                     &answers,
                                     &rid);
            if (n < 0) {
                printf("ERROR %d\n", -n);
            } else if (rid != sid) {
                printf("ERROR, ID mismatch (%#hx, %#hx)\n", sid, rid);
            } else {
                printf("%d answers\n", n);
                for (i = 0; i < n; i++) {
                    if (answers[i].type == RFC1035_TYPE_A) {
                        struct in_addr a;
                        char ipa_str[sizeof(a)];
                        memcpy(&a, answers[i].rdata, 4);
                        printf("A\t%d\t%s\n", answers[i].ttl, inet_ntop(AF_INET,&a,tmp,sizeof(a)));
                    } else if (answers[i].type == RFC1035_TYPE_PTR) {
                        char ptr[128];
                        strncpy(ptr, answers[i].rdata, answers[i].rdlength);
                        printf("PTR\t%d\t%s\n", answers[i].ttl, ptr);
                    } else {
                        fprintf(stderr, "can't print answer type %d\n",
                                (int) answers[i].type);
                    }
                }
            }
        }
    }
    return 0;
}