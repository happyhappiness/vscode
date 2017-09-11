        long port;

        /* Perform sanity checks on IP/port */
        if (inet_aton(c->argv[2]->ptr,&sa.sin_addr) == 0) {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
