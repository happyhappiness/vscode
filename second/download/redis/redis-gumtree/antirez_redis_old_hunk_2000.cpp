    if (emask & AE_READABLE) *p++ = 'r';
    if (emask & AE_WRITABLE) *p++ = 'w';
    *p = '\0';
    return sdscatprintf(sdsempty(),
        "addr=%s fd=%d name=%s age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d multi=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
        peerid,
        client->fd,
        client->name ? (char*)client->name->ptr : "",
        (long)(server.unixtime - client->ctime),
        (long)(server.unixtime - client->lastinteraction),
        flags,
        client->db->id,
        (int) dictSize(client->pubsub_channels),
        (int) listLength(client->pubsub_patterns),
        (client->flags & REDIS_MULTI) ? client->mstate.count : -1,
        (unsigned long) sdslen(client->querybuf),
        (unsigned long) sdsavail(client->querybuf),
        (unsigned long) client->bufpos,
        (unsigned long) listLength(client->reply),
        getClientOutputBufferMemoryUsage(client),
        events,
        client->lastcmd ? client->lastcmd->name : "NULL");
}
