            printf("ERROR: \"1025\"\n");
            return 1;
        }
        printf("SUCCESS\n\n");
    }

    printf("Stress with random payloads of different encoding:\n");
    {
        int i, idx, where, len;
        long long v;
        unsigned char *p;
        char buf[0x4041]; /* max length of generated string */
        zl = ziplistNew();
        for (i = 0; i < 100000; i++) {
            where = (rand() & 1) ? ZIPLIST_HEAD : ZIPLIST_TAIL;
            if (rand() & 1) {
                /* equally likely create a 16, 32 or 64 bit int */
                v = (rand() & INT16_MAX) + ((1ll << 32) >> ((rand() % 3)*16));
                v *= 2*(rand() & 1)-1; /* randomly flip sign */
                sprintf(buf, "%lld", v);
                zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), where);
            } else {
                /* equally likely generate 6, 14 or >14 bit length */
                v = rand() & 0x3f;
                v += 0x4000 >> ((rand() % 3)*8);
                memset(buf, 'x', v);
                zl = ziplistPush(zl, (unsigned char*)buf, v, where);
            }

            /* delete a random element */
            if ((len = ziplistLen(zl)) >= 10) {
                idx = rand() % len;
                // printf("Delete index %d\n", idx);
                // ziplistRepr(zl);
                ziplistDeleteRange(zl, idx, 1);
                // ziplistRepr(zl);
                len--;
            }

            /* iterate from front to back */
            idx = 0;
            p = ziplistIndex(zl, 0);
            while((p = ziplistNext(zl,p)))
                idx++;
            assert(len == idx+1);

            /* iterate from back to front */
            idx = 0;
            p = ziplistIndex(zl, -1);
            while((p = ziplistPrev(zl,p)))
                idx++;
            assert(len == idx+1);
        }
        printf("SUCCESS\n\n");
    }

    printf("Stress with variable ziplist size:\n");
