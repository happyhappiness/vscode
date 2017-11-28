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
