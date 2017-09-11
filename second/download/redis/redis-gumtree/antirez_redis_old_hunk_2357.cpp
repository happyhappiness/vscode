    } else if (c->flags & REDIS_UNIX_SOCKET) {
        cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
    } else {
        anetPeerToString(c->fd,ip,sizeof(ip),&port);
        cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ",dictid,ip,port);
    }

    for (j = 0; j < argc; j++) {
