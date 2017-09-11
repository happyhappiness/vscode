    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        /* CLUSTER MEET <ip> <port> */
        clusterNode *n;
        struct sockaddr_storage sa;
        long port;

        /* Perform sanity checks on IP/port */
        if ((inet_pton(AF_INET,c->argv[0]->ptr,&(((struct sockaddr_in *)&sa)->sin_addr)) ||
             inet_pton(AF_INET6,c->argv[0]->ptr,&(((struct sockaddr_in6 *)&sa)->sin6_addr))) == 0) {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
