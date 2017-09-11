        /* PUBLISH hello messages only to masters. */
        char ip[REDIS_IP_STR_LEN];
        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
            char myaddr[REDIS_IP_STR_LEN+128];

            // FIXME: IPv6 will break this due to nested : characters -geoffgarside
            snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
