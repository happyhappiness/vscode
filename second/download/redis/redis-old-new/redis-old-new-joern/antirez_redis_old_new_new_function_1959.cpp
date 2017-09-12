int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
    char ip[REDIS_IP_STR_LEN];
    int port;

    if (client->flags & REDIS_UNIX_SOCKET) {
        /* Unix socket client. */
        snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
        return REDIS_OK;
    } else {
        /* TCP client. */
        int retval = anetPeerToString(client->fd,ip,sizeof(ip),&port);
        if (strchr(ip,':'))
            snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
        else
            snprintf(peerid,peerid_len,"%s:%d",ip,port);
        return (retval == -1) ? REDIS_ERR : REDIS_OK;
    }
}