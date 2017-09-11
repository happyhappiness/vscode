    if (strcasecmp(master_runid, server.runid)) {
        /* Run id "?" is used by slaves that want to force a full resync. */
        if (master_runid[0] != '?') {
            serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
                master_runid, server.runid);
        } else {
            serverLog(LL_NOTICE,"Full resync requested by slave %s",
                replicationGetSlaveName(c));
        }
        goto need_full_resync;
