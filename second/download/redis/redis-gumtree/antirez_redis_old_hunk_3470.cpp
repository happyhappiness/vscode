            exit(1);
        }
        if (reply != NULL) {
            if (config.donerequests < config.requests)
                config.latency[config.donerequests++] = c->latency;
            clientDone(c);
