    *biggest_input_buffer = bib;
}

/* Turn a Redis client into an sds string representing its state. */
sds getClientInfoString(redisClient *client) {
    char ip[REDIS_IP_STR_LEN], flags[16], events[3], *p;
    int port = 0; /* initialized to zero for the unix socket case. */
    int emask;

    if (!(client->flags & REDIS_UNIX_SOCKET))
        anetPeerToString(client->fd,ip,sizeof(ip),&port);
    p = flags;
    if (client->flags & REDIS_SLAVE) {
        if (client->flags & REDIS_MONITOR)
