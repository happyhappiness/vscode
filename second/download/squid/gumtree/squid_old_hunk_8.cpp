
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
        } else if (rid != sid && rid != sidb) {
            printf("ERROR, ID mismatch (%#hx, %#hx)\n", sid, rid);
            printf("ERROR, ID mismatch (%#hx, %#hx)\n", sidb, rid);
        } else {
            printf("%d answers\n", n);

