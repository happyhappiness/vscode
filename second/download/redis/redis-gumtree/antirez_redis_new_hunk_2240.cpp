        /* sentinel known-slave */
        di2 = dictGetIterator(master->slaves);
        while((de = dictNext(di)) != NULL) {
            sentinelAddr *slave_addr;

            ri = dictGetVal(de);
            slave_addr = ri->addr;

            /* If master_addr (obtained using sentinelGetCurrentMasterAddress()
             * so it may be the address of the promoted slave) is equal to this
             * slave's address, a failover is in progress and the slave was
             * already successfully promoted. So as the address of this slave
             * we use the old master address instead. */
            if (sentinelAddrIsEqual(slave_addr,master_addr))
                slave_addr = master->addr;
            line = sdscatprintf(sdsempty(),
                "sentinel known-slave %s %s %d",
                master->name, ri->addr->ip, ri->addr->port);
