            } else {
                if (bgsaveerr != REDIS_OK) {
                    freeClient(slave);
                    redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
                    continue;
                }
                if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                    redis_fstat(slave->repldbfd,&buf) == -1) {
                    freeClient(slave);
                    redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                    continue;
                }
                slave->repldboff = 0;
