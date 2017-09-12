info = sdscatprintf(info,
            "# Memory\r\n"
            "used_memory:%zu\r\n"
            "used_memory_human:%s\r\n"
            "used_memory_rss:%zu\r\n"
            "mem_fragmentation_ratio:%.2f\r\n"
            "use_tcmalloc:%d\r\n",
            zmalloc_used_memory(),
            hmem,
            zmalloc_get_rss(),
            zmalloc_get_fragmentation_ratio(),
    #ifdef USE_TCMALLOC
            1;