        if (anetSetReuseAddr(err,s) == ANET_ERR) goto error;
        if (flags & ANET_CONNECT_NONBLOCK && anetNonBlock(err,s) != ANET_OK)
            goto error;
        if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {
            /* If the socket is non-blocking, it is ok for connect() to
             * return an EINPROGRESS error here. */
