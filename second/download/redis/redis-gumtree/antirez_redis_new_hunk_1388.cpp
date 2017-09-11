            addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
            return;
        }
        serverLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
            ri->name);
        sentinelStartFailover(ri);
        ri->flags |= SRI_FORCE_FAILOVER;
