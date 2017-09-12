
    if (fd == ANET_ERR || force) {
        if (force) close(fd);
        if (config.hostsocket == NULL) {
            fd = anetTcpConnect(err,config.hostip,config.hostport);
        } else {
            fd = anetUnixConnect(err,config.hostsocket);
        }
        if (fd == ANET_ERR) {
            fprintf(stderr,"Could not connect to Redis at ");
            if (config.hostsocket == NULL)
                fprintf(stderr,"%s:%d: %s",config.hostip,config.hostport,err);
            else
                fprintf(stderr,"%s: %s",config.hostsocket,err);
            return -1;
        }
        anetTcpNoDelay(NULL,fd);
