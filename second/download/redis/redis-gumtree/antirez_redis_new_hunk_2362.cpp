    *biggest_input_buffer = bib;
}

/* A Redis "Peer ID" is a colon separated ip:port pair.
 * For IPv4 it's in the form x.y.z.k:pork, example: "127.0.0.1:1234".
 * For IPv6 addresses we use [] around the IP part, like in "[::1]:1234".
 * For Unix socekts we use path:0, like in "/tmp/redis:0".
 *
 * A Peer ID always fits inside a buffer of REDIS_PEER_ID_LEN bytes, including
 * the null term.
 *
 * The function is always successful, but if the IP or port can't be extracted
 * for some reason, "?" and "0" are used (this is the semantics of
 * anetPeerToString() from anet.c). In practical terms this should never
 * happen. */
void getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
    char ip[REDIS_IP_STR_LEN];
    int port;

    if (client->flags & REDIS_UNIX_SOCKET) {
        /* Unix socket client. */
        snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
        return;
    } else {
        /* TCP client. */
        anetPeerToString(client->fd,ip,sizeof(ip),&port);
        if (strchr(ip,':'))
            snprintf(peerid,peerid_len,"[%s]:%d",ip,port);
        else
            snprintf(peerid,peerid_len,"%s:%d",ip,port);
    }
}

/* Turn a Redis client into an sds string representing its state. */
sds getClientInfoString(redisClient *client) {
    char peerid[REDIS_PEER_ID_LEN], flags[16], events[3], *p;
    int emask;

    getClientPeerId(client,peerid,sizeof(peerid));
    p = flags;
    if (client->flags & REDIS_SLAVE) {
        if (client->flags & REDIS_MONITOR)
