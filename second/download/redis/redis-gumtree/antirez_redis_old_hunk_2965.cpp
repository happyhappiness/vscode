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

void clientCommand(redisClient *c) {
