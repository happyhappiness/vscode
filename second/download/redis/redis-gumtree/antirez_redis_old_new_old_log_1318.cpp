info = sdscatprintf(info,
            "# Memory\r\n"
            "used_memory:%zu\r\n"
            "used_memory_human:%s\r\n"
            "used_memory_rss:%zu\r\n"
            "used_memory_peak:%zu\r\n"
            "used_memory_peak_human:%s\r\n"
            "total_system_memory:%lu\r\n"
            "total_system_memory_human:%s\r\n"
            "used_memory_lua:%lld\r\n"
            "mem_fragmentation_ratio:%.2f\r\n"
            "mem_allocator:%s\r\n"
            "maxmemory_policy:%s\r\n",
            zmalloc_used,
            hmem,
            server.resident_set_size,
            server.stat_peak_memory,
            peak_hmem,
            (unsigned long)total_system_mem,
            total_system_hmem,
            ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
            zmalloc_get_fragmentation_ratio(server.resident_set_size),
            ZMALLOC_LIB,
            evict_policy;