
            stopAppendOnly();
            while (retry-- && startAppendOnly() == REDIS_ERR) {
                serverLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                sleep(1);
            }
            if (!retry) {
                serverLog(REDIS_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                exit(1);
            }
        }
