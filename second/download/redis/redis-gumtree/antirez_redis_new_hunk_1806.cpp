            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
            redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
        }
    } else if (server.rdb_child_pid != -1 &&
               server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
    {
        /* There is an RDB child process but it is writing directly to
         * children sockets. We need to wait for the next BGSAVE
         * in order to synchronize. */
        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
        redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
    } else {
        if (server.repl_diskless) {
            /* Diskless replication RDB child is created inside
             * replicationCron() since we want to delay its start a
             * few seconds to wait for more slaves to arrive. */
            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
            redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Ok we don't have a BGSAVE in progress, let's start one. */
            redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
            if (startBgsaveForReplication() != REDIS_OK) {
                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
                return;
            }
            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
        }
    }

    if (server.repl_disable_tcp_nodelay)
