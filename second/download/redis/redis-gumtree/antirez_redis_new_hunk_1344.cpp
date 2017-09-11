             * diskless replication, our work is trivial, we can just put
             * the slave online. */
            if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
                serverLog(REDIS_NOTICE,
                    "Streamed RDB transfer with slave %s succeeded (socket). Waiting for REPLCONF ACK from slave to enable streaming",
                        replicationGetSlaveName(slave));
                /* Note: we wait for a REPLCONF ACK message from slave in
