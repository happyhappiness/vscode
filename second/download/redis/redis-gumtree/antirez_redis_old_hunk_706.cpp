            /* Diskless replication RDB child is created inside
             * replicationCron() since we want to delay its start a
             * few seconds to wait for more slaves to arrive. */
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
            if (server.repl_diskless_sync_delay)
                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Target is disk (or the slave is not capable of supporting
             * diskless replication) and we don't have a BGSAVE in progress,
             * let's start one. */
            if (startBgsaveForReplication(c->slave_capa) != C_OK) {
                serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
                return;
            }
            replicationSetupSlaveForFullResync(c,getPsyncInitialOffset());
        }
    }

    if (server.repl_disable_tcp_nodelay)
        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
    c->repldbfd = -1;
    c->flags |= CLIENT_SLAVE;
    listAddNodeTail(server.slaves,c);
    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
        createReplicationBacklog();
    return;
