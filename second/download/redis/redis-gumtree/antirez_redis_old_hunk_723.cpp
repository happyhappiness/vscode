            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
        }
    } else if (server.rdb_child_pid != -1 &&
               server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
    {
