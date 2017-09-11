        long port;

        /* Perform sanity checks on IP/port */
        if (inet_pton(AF_INET,c->argv[0]->ptr,&(sa.sin_addr)) == 0) {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
