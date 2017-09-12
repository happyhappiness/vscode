    client c = zmalloc(sizeof(struct _client));
    char err[ANET_ERR_LEN];

    if (config.hostsocket == NULL)
        c->fd = anetTcpNonBlockConnect(err,config.hostip,config.hostport);
    else
        c->fd = anetUnixNonBlockConnect(err,config.hostsocket);

    if (c->fd == ANET_ERR) {
        zfree(c);
        fprintf(stderr,"Connect: %s\n",err);
