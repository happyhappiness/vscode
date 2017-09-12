info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "redis_git_sha1:%s\r\n"
        "redis_git_dirty:%d\r\n"
        "arch_bits:%s\r\n"
        "multiplexing_api:%s\r\n"
        "process_id:%ld\r\n"
        "uptime_in_seconds:%ld\r\n"
        "uptime_in_days:%ld\r\n"
        "lru_clock:%ld\r\n"
        "used_cpu_sys:%.2f\r\n"
        "used_cpu_user:%.2f\r\n"
        "used_cpu_sys_childrens:%.2f\r\n"
        "used_cpu_user_childrens:%.2f\r\n"
        "connected_clients:%d\r\n"
        "connected_slaves:%d\r\n"
        "client_longest_output_list:%lu\r\n"
        "client_biggest_input_buf:%lu\r\n"
        "blocked_clients:%d\r\n"
        "used_memory:%zu\r\n"
        "used_memory_human:%s\r\n"
        "used_memory_rss:%zu\r\n"
        "mem_fragmentation_ratio:%.2f\r\n"
        "use_tcmalloc:%d\r\n"
        "loading:%d\r\n"
        "aof_enabled:%d\r\n"
        "changes_since_last_save:%lld\r\n"
        "bgsave_in_progress:%d\r\n"
        "last_save_time:%ld\r\n"
        "bgrewriteaof_in_progress:%d\r\n"
        "total_connections_received:%lld\r\n"
        "total_commands_processed:%lld\r\n"
        "expired_keys:%lld\r\n"
        "evicted_keys:%lld\r\n"
        "keyspace_hits:%lld\r\n"
        "keyspace_misses:%lld\r\n"
        "hash_max_zipmap_entries:%zu\r\n"
        "hash_max_zipmap_value:%zu\r\n"
        "pubsub_channels:%ld\r\n"
        "pubsub_patterns:%u\r\n"
        "ds_enabled:%d\r\n"
        "role:%s\r\n"
        ,REDIS_VERSION,
        redisGitSHA1(),
        strtol(redisGitDirty(),NULL,10) > 0,
        (sizeof(long) == 8) ? "64" : "32",
        aeGetApiName(),
        (long) getpid(),
        uptime,
        uptime/(3600*24),
        (unsigned long) server.lruclock,
        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
        listLength(server.clients)-listLength(server.slaves),
        listLength(server.slaves),
        lol, bib,
        server.bpop_blocked_clients,
        zmalloc_used_memory(),
        hmem,
        zmalloc_get_rss(),
        zmalloc_get_fragmentation_ratio(),
#ifdef USE_TCMALLOC
        1,
#else
        0,
#endif
        server.loading,
        server.appendonly,
        server.dirty,
        server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t) -1,
        server.lastsave,
        server.bgrewritechildpid != -1,
        server.stat_numconnections,
        server.stat_numcommands,
        server.stat_expiredkeys,
        server.stat_evictedkeys,
        server.stat_keyspace_hits,
        server.stat_keyspace_misses,
        server.hash_max_zipmap_entries,
        server.hash_max_zipmap_value,
        dictSize(server.pubsub_channels),
        listLength(server.pubsub_patterns),
        server.ds_enabled != 0,
        server.masterhost == NULL ? "master" : "slave"
    );