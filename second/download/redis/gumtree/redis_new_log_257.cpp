info = sdscatprintf(info,
            "# Memory\r\n"
            "used_memory:%zu\r\n"
            "used_memory_human:%s\r\n"
            "used_memory_rss:%zu\r\n"
            "used_memory_peak:%zu\r\n"
            "used_memory_peak_human:%s\r\n"
            "used_memory_lua:%lld\r\n"
            "mem_fragmentation_ratio:%.2f\r\n"
            "mem_allocator:%s\r\n",
            zmalloc_used,
            hmem,
            zmalloc_get_rss(),
            server.stat_peak_memory,
            peak_hmem,
            ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
            zmalloc_get_fragmentation_ratio(),;