        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
            char myaddr[REDIS_IP_STR_LEN+128];

            snprintf(myaddr,sizeof(myaddr),"%s,%d,%s,%d",
                ip, server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);
            retval = redisAsyncCommand(ri->cc,
