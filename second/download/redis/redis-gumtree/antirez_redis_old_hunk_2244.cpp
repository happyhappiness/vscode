            sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);

            snprintf(payload,sizeof(payload),
                "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
                "%s,%s,%d,%lld",    /* Info about current master. */
                ip, server.port, server.runid,
                (master->flags & SRI_CAN_FAILOVER) != 0,
                (unsigned long long) sentinel.current_epoch,
                /* --- */
                master->name,master_addr->ip,master_addr->port,
