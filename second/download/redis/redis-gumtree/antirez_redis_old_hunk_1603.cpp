        bytesToHuman(total_system_hmem,total_system_mem);
        bytesToHuman(used_memory_lua_hmem,memory_lua);
        bytesToHuman(used_memory_rss_hmem,server.resident_set_size);

        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
