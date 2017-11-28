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
    while (fgets(input, 512, stdin)) {
        struct in_addr junk;
        strtok(input, "\r\n");
        memset(buf, '\0', 512);
        sz = 512;
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
        memset(rbuf, '\0', 512);
        rl = recv(s, rbuf, 512, 0);
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
                printf("ERROR %d\n", rfc1035_errno);
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