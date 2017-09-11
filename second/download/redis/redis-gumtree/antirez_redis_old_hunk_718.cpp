            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
        }

    /* CASE 2: BGSAVE is in progress and replication target is socket. */
    } else if (server.rdb_child_pid != -1 &&
               server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
    {
