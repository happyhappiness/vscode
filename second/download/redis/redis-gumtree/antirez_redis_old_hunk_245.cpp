        bytesToHuman(used_memory_rss_hmem,server.resident_set_size);
        bytesToHuman(maxmemory_hmem,server.maxmemory);

        size_t net_usage = 1;
        if (zmalloc_used > mh->startup_allocated)
            net_usage = zmalloc_used - mh->startup_allocated;

        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Memory\r\n"
