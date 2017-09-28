                    fprintf(stderr,"Unexpected error reply, exiting...\n");
                    exit(1);
                }

                freeReplyObject(reply);

                if (c->selectlen) {
                    int j;

                    /* This is the OK from SELECT. Just discard the SELECT
                     * from the buffer. */
                    c->pending--;
                    sdsrange(c->obuf,c->selectlen,-1);
                    /* We also need to fix the pointers to the strings
                     * we need to randomize. */
                    for (j = 0; j < c->randlen; j++)
                        c->randptr[j] -= c->selectlen;
                    c->selectlen = 0;
                    continue;
                }

                if (config.requests_finished < config.requests)
                    config.latency[config.requests_finished++] = c->latency;
                c->pending--;
                if (c->pending == 0) {
                    clientDone(c);
                    break;
