        long port;

        /* Perform sanity checks on IP/port */
        if (inet_pton(AF_INET,c->argv[2]->ptr,
            &(((struct sockaddr_in *)&sa)->sin_addr)))
        {
            sa.ss_family = AF_INET;
        } else if (inet_pton(AF_INET6,c->argv[2]->ptr,
            &(((struct sockaddr_in6 *)&sa)->sin6_addr)))
        {
            sa.ss_family = AF_INET6;
        } else {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
