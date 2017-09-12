serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                "Replication ID mismatch (Slave asked for '%s', my replication "
                "ID is '%s')",
                master_replid, server.replid);