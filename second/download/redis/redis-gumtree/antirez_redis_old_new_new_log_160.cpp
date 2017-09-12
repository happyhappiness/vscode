serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                    "Replication ID mismatch (Slave asked for '%s', my "
                    "replication IDs are '%s' and '%s')",
                    master_replid, server.replid, server.replid2);