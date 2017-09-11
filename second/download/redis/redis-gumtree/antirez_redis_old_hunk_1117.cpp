            int retry = 10;

            stopAppendOnly();
            while (retry-- && startAppendOnly() == REDIS_ERR) {
                serverLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                sleep(1);
            }
