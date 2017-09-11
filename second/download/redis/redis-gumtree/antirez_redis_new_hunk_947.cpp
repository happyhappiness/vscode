    if (server.cached_master) {
        psync_runid = server.cached_master->replrunid;
        snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
        serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
    } else {
        serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
        psync_runid = "?";
        memcpy(psync_offset,"-1",3);
    }
