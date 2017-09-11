            /* If we have AOF enabled but haven't written the AOF yet, don't
             * shutdown or else the dataset will be lost. */
            if (server.aof_state == REDIS_AOF_WAIT_REWRITE) {
                redisLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
                return REDIS_ERR;
            }
            redisLog(REDIS_WARNING,
                "There is a child rewriting the AOF. Killing it!");
            kill(server.aof_child_pid,SIGUSR1);
        }
        /* Append only file: fsync() the AOF and exit */
        redisLog(REDIS_NOTICE,"Calling fsync() on the AOF file.");
        aof_fsync(server.aof_fd);
    }
    if ((server.saveparamslen > 0 && !nosave) || save) {
        redisLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
        /* Snapshotting. Perform a SYNC SAVE and exit */
        if (rdbSave(server.rdb_filename) != REDIS_OK) {
            /* Ooops.. error saving! The best we can do is to continue
             * operating. Note that if there was a background saving process,
             * in the next cron() Redis will be notified that the background
             * saving aborted, handling special stuff like slaves pending for
             * synchronization... */
            redisLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
            return REDIS_ERR;
        }
    }
    if (server.daemonize || server.pidfile) {
        redisLog(REDIS_NOTICE,"Removing the pid file.");
        unlink(server.pidfile);
    }
    /* Close the listening sockets. Apparently this allows faster restarts. */
    closeListeningSockets(1);
    redisLog(REDIS_WARNING,"%s is now ready to exit, bye bye...",
        server.sentinel_mode ? "Sentinel" : "Redis");
    return REDIS_OK;
}
