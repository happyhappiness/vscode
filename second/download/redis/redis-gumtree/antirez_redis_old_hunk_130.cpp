        /* Restart the AOF subsystem now that we finished the sync. This
         * will trigger an AOF rewrite, and when done will start appending
         * to the new file. */
        if (server.aof_state != AOF_OFF) {
            int retry = 10;

            stopAppendOnly();
            while (retry-- && startAppendOnly() == C_ERR) {
                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                sleep(1);
            }
            if (!retry) {
                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                exit(1);
            }
        }
    }

    return;
