static sds genRedisInfoString(void) {
    sds info;
    time_t uptime = time(NULL)-server.stat_starttime;
    int j;
    char hmem[64];

    bytesToHuman(hmem,zmalloc_used_memory());
    info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "redis_git_sha1:%s\r\n"
        "redis_git_dirty:%d\r\n"
        "arch_bits:%s\r\n"
        "multiplexing_api:%s\r\n"
        "process_id:%ld\r\n"
        "uptime_in_seconds:%ld\r\n"
        "uptime_in_days:%ld\r\n"
        "connected_clients:%d\r\n"
        "connected_slaves:%d\r\n"
        "blocked_clients:%d\r\n"
        "used_memory:%zu\r\n"
        "used_memory_human:%s\r\n"
        "changes_since_last_save:%lld\r\n"
        "bgsave_in_progress:%d\r\n"
        "last_save_time:%ld\r\n"
        "bgrewriteaof_in_progress:%d\r\n"
        "total_connections_received:%lld\r\n"
        "total_commands_processed:%lld\r\n"
        "expired_keys:%lld\r\n"
        "hash_max_zipmap_entries:%zu\r\n"
        "hash_max_zipmap_value:%zu\r\n"
        "pubsub_channels:%ld\r\n"
        "pubsub_patterns:%u\r\n"
        "vm_enabled:%d\r\n"
        "role:%s\r\n"
        ,REDIS_VERSION,
        REDIS_GIT_SHA1,
        REDIS_GIT_DIRTY > 0,
        (sizeof(long) == 8) ? "64" : "32",
        aeGetApiName(),
        (long) getpid(),
        uptime,
        uptime/(3600*24),
        listLength(server.clients)-listLength(server.slaves),
        listLength(server.slaves),
        server.blpop_blocked_clients,
        zmalloc_used_memory(),
        hmem,
        server.dirty,
        server.bgsavechildpid != -1,
        server.lastsave,
        server.bgrewritechildpid != -1,
        server.stat_numconnections,
        server.stat_numcommands,
        server.stat_expiredkeys,
        server.hash_max_zipmap_entries,
        server.hash_max_zipmap_value,
        dictSize(server.pubsub_channels),
        listLength(server.pubsub_patterns),
        server.vm_enabled != 0,
        server.masterhost == NULL ? "master" : "slave"
    );
    if (server.masterhost) {
        info = sdscatprintf(info,
            "master_host:%s\r\n"
            "master_port:%d\r\n"
            "master_link_status:%s\r\n"
            "master_last_io_seconds_ago:%d\r\n"
            ,server.masterhost,
            server.masterport,
            (server.replstate == REDIS_REPL_CONNECTED) ?
                "up" : "down",
            server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1
        );
    }
    if (server.vm_enabled) {
        lockThreadedIO();
        info = sdscatprintf(info,
            "vm_conf_max_memory:%llu\r\n"
            "vm_conf_page_size:%llu\r\n"
            "vm_conf_pages:%llu\r\n"
            "vm_stats_used_pages:%llu\r\n"
            "vm_stats_swapped_objects:%llu\r\n"
            "vm_stats_swappin_count:%llu\r\n"
            "vm_stats_swappout_count:%llu\r\n"
            "vm_stats_io_newjobs_len:%lu\r\n"
            "vm_stats_io_processing_len:%lu\r\n"
            "vm_stats_io_processed_len:%lu\r\n"
            "vm_stats_io_active_threads:%lu\r\n"
            "vm_stats_blocked_clients:%lu\r\n"
            ,(unsigned long long) server.vm_max_memory,
            (unsigned long long) server.vm_page_size,
            (unsigned long long) server.vm_pages,
            (unsigned long long) server.vm_stats_used_pages,
            (unsigned long long) server.vm_stats_swapped_objects,
            (unsigned long long) server.vm_stats_swapins,
            (unsigned long long) server.vm_stats_swapouts,
            (unsigned long) listLength(server.io_newjobs),
            (unsigned long) listLength(server.io_processing),
            (unsigned long) listLength(server.io_processed),
            (unsigned long) server.io_active_threads,
            (unsigned long) server.vm_blocked_clients
        );
        unlockThreadedIO();
    }
    for (j = 0; j < server.dbnum; j++) {
        long long keys, vkeys;

        keys = dictSize(server.db[j].dict);
        vkeys = dictSize(server.db[j].expires);
        if (keys || vkeys) {
            info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
                j, keys, vkeys);
        }
    }
    return info;
}