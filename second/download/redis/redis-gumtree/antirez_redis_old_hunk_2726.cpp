    if (emask & AE_WRITABLE) *p++ = 'w';
    *p = '\0';
    return sdscatprintf(sdsempty(),
        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
        ip,port,client->fd,
        (long)(server.unixtime - client->ctime),
        (long)(server.unixtime - client->lastinteraction),
        flags,
        client->db->id,
        (int) dictSize(client->pubsub_channels),
        (int) listLength(client->pubsub_patterns),
        (unsigned long) sdslen(client->querybuf),
        (unsigned long) sdsavail(client->querybuf),
        (unsigned long) client->bufpos,
