snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
                ip, server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);