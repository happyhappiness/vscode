    } else if (c->flags & REDIS_UNIX_SOCKET) {
        cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
    } else {
        getClientPeerId(c,peerid,sizeof(peerid));
        cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,peerid);
    }

    for (j = 0; j < argc; j++) {
