snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
                inet_ntoa(sa.sin_addr), server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);