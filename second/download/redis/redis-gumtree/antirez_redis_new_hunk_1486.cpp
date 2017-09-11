    }

    /* Create the socket */
    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
                                atoi(c->argv[2]->ptr));
    if (fd == -1) {
        sdsfree(name);
        addReplyErrorFormat(c,"Can't connect to target node: %s",
