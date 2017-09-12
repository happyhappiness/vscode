sdscatprintf(sdsempty(),"+FULLRESYNC %s %lld\r\n",
        server.runid,
        psync_offset);