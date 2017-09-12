static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
{
    int s, rv;
    char _port[6];  /* strlen("65535"); */
    struct addrinfo hints, *servinfo, *p;

    snprintf(_port,6,"%d",port);
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(addr,_port,&hints,&servinfo)) != 0) {
        anetSetError(err, "%s", gai_strerror(rv));
        return ANET_ERR;
    }
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((s = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
            continue;

        /* if we set err then goto cleanup, otherwise next */
        if (anetSetReuseAddr(err,s) == ANET_ERR) {
            goto error;
        }
        if (flags & ANET_CONNECT_NONBLOCK) {
            if (anetNonBlock(err,s) != ANET_OK)
                goto error;
        }
        if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
            if (errno == EINPROGRESS &&
                flags & ANET_CONNECT_NONBLOCK)
                goto end;

            close(s);
            continue;
        }

        /* break with the socket */
        goto end;
    }
    if (p == NULL) {
        anetSetError(err, "creating socket: %s", strerror(errno));
        goto error;
    }

error:
    s = ANET_ERR;
end:
    freeaddrinfo(servinfo);
    return s;
}