                    fprintf(stderr,"Unexpected error reply, exiting...\n");
                    exit(1);
                }

                freeReplyObject(reply);

                if (config.requests_finished < config.requests)
                    config.latency[config.requests_finished++] = c->latency;
                c->pending--;
                if (c->pending == 0) {
                    clientDone(c);
                    break;
