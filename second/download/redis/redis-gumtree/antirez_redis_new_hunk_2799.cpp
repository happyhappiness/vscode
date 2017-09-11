    if (emask & AE_WRITABLE) *p++ = 'w';
    *p = '\0';
    return sdscatprintf(sdsempty(),
        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
        ip,port,client->fd,
        (long)(now - client->ctime),
        (long)(now - client->lastinteraction),
        flags,
        client->db->id,
