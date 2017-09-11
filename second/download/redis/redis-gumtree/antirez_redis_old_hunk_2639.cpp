    gettimeofday(&tv,NULL);
    cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
    if (c->flags & REDIS_LUA_CLIENT) {
        cmdrepr = sdscatprintf(cmdrepr,"[%d lua] ", dictid);
    } else {
        anetPeerToString(c->fd,ip,&port);
        cmdrepr = sdscatprintf(cmdrepr,"[%d %s:%d] ", dictid,ip,port);
    }

    for (j = 0; j < argc; j++) {
