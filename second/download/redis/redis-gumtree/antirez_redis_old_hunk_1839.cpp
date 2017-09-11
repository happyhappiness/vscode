    char ip[REDIS_IP_STR_LEN];
    char payload[REDIS_IP_STR_LEN+1024];
    int retval;
    char *announceIP;
    int port;
    sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
    sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);

    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;

    /* Use the specified announce address if specified, otherwise try to
     * obtain our own IP address. */
    if (sentinel.announce_addr) {
        announceIP = sentinel.announce_addr->ip;
        port = sentinel.announce_addr->port;
    } else {
        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1)
            return REDIS_ERR;
        announceIP = ip;
        port = server.port;
    }

    /* Format and send the Hello message. */
    snprintf(payload,sizeof(payload),
        "%s,%d,%s,%llu," /* Info about this sentinel. */
        "%s,%s,%d,%llu", /* Info about current master. */
        announceIP, port, server.runid,
        (unsigned long long) sentinel.current_epoch,
        /* --- */
        master->name,master_addr->ip,master_addr->port,
