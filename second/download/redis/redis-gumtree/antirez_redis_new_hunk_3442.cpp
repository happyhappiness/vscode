            exit(1);
        }
        if (reply != NULL) {
            if (reply == (void*)REDIS_REPLY_ERROR) {
                fprintf(stderr,"Unexpected error reply, exiting...\n");
                exit(1);
            }

            if (config.donerequests < config.requests)
                config.latency[config.donerequests++] = c->latency;
            clientDone(c);
