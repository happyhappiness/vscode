void syncCommand(client *c) {
    /* ignore SYNC if already slave or in monitor mode */
    if (c->flags & CLIENT_SLAVE) return;

    /* Refuse SYNC requests if we are a slave but the link with our master
     * is not ok... */
    if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED) {
        addReplyError(c,"Can't SYNC while not connected with my master");
        return;
    }

    /* SYNC can't be issued when the server has pending data to send to
     * the client about already issued commands. We need a fresh reply
     * buffer registering the differences between the BGSAVE and the current
     * dataset, so that we can copy to other slaves if needed. */
    if (listLength(c->reply) != 0 || c->bufpos != 0) {
        addReplyError(c,"SYNC and PSYNC are invalid with pending output");
        return;
    }

    serverLog(LL_NOTICE,"Slave %s asks for synchronization",
        replicationGetSlaveName(c));

    /* Try a partial resynchronization if this is a PSYNC command.
     * If it fails, we continue with usual full resynchronization, however
     * when this happens masterTryPartialResynchronization() already
     * replied with:
     *
     * +FULLRESYNC <runid> <offset>
     *
     * So the slave knows the new runid and offset to try a PSYNC later
     * if the connection with the master is lost. */
    if (!strcasecmp(c->argv[0]->ptr,"psync")) {
        if (masterTryPartialResynchronization(c) == C_OK) {
            server.stat_sync_partial_ok++;
            return; /* No full resync needed, return. */
        } else {
            char *master_runid = c->argv[1]->ptr;

            /* Increment stats for failed PSYNCs, but only if the
             * runid is not "?", as this is used by slaves to force a full
             * resync on purpose when they are not albe to partially
             * resync. */
            if (master_runid[0] != '?') server.stat_sync_partial_err++;
        }
    } else {
        /* If a slave uses SYNC, we are dealing with an old implementation
         * of the replication protocol (like redis-cli --slave). Flag the client
         * so that we don't expect to receive REPLCONF ACK feedbacks. */
        c->flags |= CLIENT_PRE_PSYNC;
    }

    /* Full resynchronization. */
    server.stat_sync_full++;

    /* Here we need to check if there is a background saving operation
     * in progress, or if it is required to start one */
    if (server.rdb_child_pid != -1 &&
        server.rdb_child_type == RDB_CHILD_TYPE_DISK)
    {
        /* Ok a background save is in progress. Let's check if it is a good
         * one for replication, i.e. if there is another slave that is
         * registering differences since the server forked to save. */
        client *slave;
        listNode *ln;
        listIter li;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            slave = ln->value;
            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) break;
        }
        if (ln) {
            /* Perfect, the server is already registering differences for
             * another slave. Set the right state, and copy the buffer. */
            copyClientOutputBuffer(c,slave);
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
            serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
        } else {
            /* No way, we need to wait for the next BGSAVE in order to
             * register differences. */
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
        }
    } else if (server.rdb_child_pid != -1 &&
               server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
    {
        /* There is an RDB child process but it is writing directly to
         * children sockets. We need to wait for the next BGSAVE
         * in order to synchronize. */
        c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
    } else {
        if (server.repl_diskless_sync) {
            /* Diskless replication RDB child is created inside
             * replicationCron() since we want to delay its start a
             * few seconds to wait for more slaves to arrive. */
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
            if (server.repl_diskless_sync_delay)
                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
        } else {
            /* Ok we don't have a BGSAVE in progress, let's start one. */
            if (startBgsaveForReplication() != C_OK) {
                serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                addReplyError(c,"Unable to perform background save");
                return;
            }
            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
        }
    }

    if (server.repl_disable_tcp_nodelay)
        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
    c->repldbfd = -1;
    c->flags |= CLIENT_SLAVE;
    server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
    listAddNodeTail(server.slaves,c);
    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
        createReplicationBacklog();
    return;
}