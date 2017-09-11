            listIter li;

            listRewind(server.slaves,&li);
            serverLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
            while((ln = listNext(&li))) {
                redisClient *slave = ln->value;

