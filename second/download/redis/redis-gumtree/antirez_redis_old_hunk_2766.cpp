    if (emask & AE_WRITABLE) *p++ = 'w';
    *p = '\0';
    return sdscatprintf(sdsempty(),
        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
        ip,port,client->fd,
        (long)(now - client->lastinteraction),
        flags,
        client->db->id,
        (int) dictSize(client->pubsub_channels),
        (int) listLength(client->pubsub_patterns),
        (unsigned long) sdslen(client->querybuf),
        (unsigned long) client->bufpos,
        (unsigned long) listLength(client->reply),
        getClientOutputBufferMemoryUsage(client),
