    {
        /* Run id "?" is used by slaves that want to force a full resync. */
        if (master_replid[0] != '?') {
            serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                "Replication ID mismatch (Slave asked for '%s', my replication "
                "ID is '%s')",
                master_replid, server.replid);
        } else {
            serverLog(LL_NOTICE,"Full resync requested by slave %s",
                replicationGetSlaveName(c));
