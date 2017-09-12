sds getClientInfoString(redisClient *client) {
    char ip[32], flags[16], *p;
    int port;
    time_t now = time(NULL);

    if (anetPeerToString(client->fd,ip,&port) == -1) {
        ip[0] = '?';
        ip[1] = '\0';
        port = 0;
    }
    p = flags;
    if (client->flags & REDIS_SLAVE) {
        if (client->flags & REDIS_MONITOR)
            *p++ = 'O';
        else
            *p++ = 'S';
    }
    if (client->flags & REDIS_MASTER) *p++ = 'M';
    if (p == flags) *p++ = 'N';
    if (client->flags & REDIS_MULTI) *p++ = 'x';
    if (client->flags & REDIS_BLOCKED) *p++ = 'b';
    if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
    if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
    if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
    *p++ = '\0';
    return sdscatprintf(sdsempty(),
        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d",
        ip,port,client->fd,
        (long)(now - client->lastinteraction),
        flags,
        client->db->id,
        (int) dictSize(client->pubsub_channels),
        (int) listLength(client->pubsub_patterns));
}