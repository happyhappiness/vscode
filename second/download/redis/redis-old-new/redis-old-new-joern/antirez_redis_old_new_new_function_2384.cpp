sds genRedisInfoString(char *section) {
    sds info = sdsempty();
    time_t uptime = server.unixtime-server.stat_starttime;
    int j, numcommands;
    struct rusage self_ru, c_ru;
    unsigned long lol, bib;
    int allsections = 0, defsections = 0;
    int sections = 0;
    
    if (section) {
        allsections = strcasecmp(section,"all") == 0;
        defsections = strcasecmp(section,"default") == 0;
    }

    getrusage(RUSAGE_SELF, &self_ru);
    getrusage(RUSAGE_CHILDREN, &c_ru);
    getClientsMaxBuffers(&lol,&bib);

    /* Server */
    if (allsections || defsections || !strcasecmp(section,"server")) {
        struct utsname name;

        if (sections++) info = sdscat(info,"\r\n");
        uname(&name);
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
            "redis_git_sha1:%s\r\n"
            "redis_git_dirty:%d\r\n"
            "os:%s %s %s\r\n"
            "arch_bits:%d\r\n"
            "multiplexing_api:%s\r\n"
            "gcc_version:%d.%d.%d\r\n"
            "process_id:%ld\r\n"
            "run_id:%s\r\n"
            "tcp_port:%d\r\n"
            "uptime_in_seconds:%ld\r\n"
            "uptime_in_days:%ld\r\n"
            "lru_clock:%ld\r\n",
            REDIS_VERSION,
            redisGitSHA1(),
            strtol(redisGitDirty(),NULL,10) > 0,
            name.sysname, name.release, name.machine,
            server.arch_bits,
            aeGetApiName(),
#ifdef __GNUC__
            __GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__,
#else
            0,0,0,
#endif
            (long) getpid(),
            server.runid,
            server.port,
            uptime,
            uptime/(3600*24),
            (unsigned long) server.lruclock);
    }

    /* Clients */
    if (allsections || defsections || !strcasecmp(section,"clients")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Clients\r\n"
            "connected_clients:%lu\r\n"
            "client_longest_output_list:%lu\r\n"
            "client_biggest_input_buf:%lu\r\n"
            "blocked_clients:%d\r\n",
            listLength(server.clients)-listLength(server.slaves),
            lol, bib,
            server.bpop_blocked_clients);
    }

    /* Memory */
    if (allsections || defsections || !strcasecmp(section,"memory")) {
        char hmem[64];
        char peak_hmem[64];

        bytesToHuman(hmem,zmalloc_used_memory());
        bytesToHuman(peak_hmem,server.stat_peak_memory);
        if (sections++) info = sdscat(info,"\r\n");
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
            zmalloc_used_memory(),
            hmem,
            zmalloc_get_rss(),
            server.stat_peak_memory,
            peak_hmem,
            ((long long)lua_gc(server.lua,LUA_GCCOUNT,0))*1024LL,
            zmalloc_get_fragmentation_ratio(),
            ZMALLOC_LIB
            );
    }

    /* Persistence */
    if (allsections || defsections || !strcasecmp(section,"persistence")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Persistence\r\n"
            "loading:%d\r\n"
            "aof_enabled:%d\r\n"
            "changes_since_last_save:%lld\r\n"
            "bgsave_in_progress:%d\r\n"
            "last_save_time:%ld\r\n"
            "last_bgsave_status:%s\r\n"
            "bgrewriteaof_in_progress:%d\r\n",
            server.loading,
            server.aof_state != REDIS_AOF_OFF,
            server.dirty,
            server.rdb_child_pid != -1,
            server.lastsave,
            server.lastbgsave_status == REDIS_OK ? "ok" : "err",
            server.aof_child_pid != -1);

        if (server.aof_state != REDIS_AOF_OFF) {
            info = sdscatprintf(info,
                "aof_current_size:%lld\r\n"
                "aof_base_size:%lld\r\n"
                "aof_pending_rewrite:%d\r\n"
                "aof_buffer_length:%zu\r\n"
                "aof_pending_bio_fsync:%llu\r\n"
                "aof_delayed_fsync:%lu\r\n",
                (long long) server.aof_current_size,
                (long long) server.aof_rewrite_base_size,
                server.aof_rewrite_scheduled,
                sdslen(server.aof_buf),
                bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC),
                server.aof_delayed_fsync);
        }

        if (server.loading) {
            double perc;
            time_t eta, elapsed;
            off_t remaining_bytes = server.loading_total_bytes-
                                    server.loading_loaded_bytes;

            perc = ((double)server.loading_loaded_bytes /
                   server.loading_total_bytes) * 100;

            elapsed = server.unixtime-server.loading_start_time;
            if (elapsed == 0) {
                eta = 1; /* A fake 1 second figure if we don't have
                            enough info */
            } else {
                eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
            }

            info = sdscatprintf(info,
                "loading_start_time:%ld\r\n"
                "loading_total_bytes:%llu\r\n"
                "loading_loaded_bytes:%llu\r\n"
                "loading_loaded_perc:%.2f\r\n"
                "loading_eta_seconds:%ld\r\n"
                ,(unsigned long) server.loading_start_time,
                (unsigned long long) server.loading_total_bytes,
                (unsigned long long) server.loading_loaded_bytes,
                perc,
                eta
            );
        }
    }

    /* Stats */
    if (allsections || defsections || !strcasecmp(section,"stats")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Stats\r\n"
            "total_connections_received:%lld\r\n"
            "total_commands_processed:%lld\r\n"
            "instantaneous_ops_per_sec:%lld\r\n"
            "rejected_connections:%lld\r\n"
            "expired_keys:%lld\r\n"
            "evicted_keys:%lld\r\n"
            "keyspace_hits:%lld\r\n"
            "keyspace_misses:%lld\r\n"
            "pubsub_channels:%ld\r\n"
            "pubsub_patterns:%lu\r\n"
            "latest_fork_usec:%lld\r\n",
            server.stat_numconnections,
            server.stat_numcommands,
            getOperationsPerSecond(),
            server.stat_rejected_conn,
            server.stat_expiredkeys,
            server.stat_evictedkeys,
            server.stat_keyspace_hits,
            server.stat_keyspace_misses,
            dictSize(server.pubsub_channels),
            listLength(server.pubsub_patterns),
            server.stat_fork_time);
    }

    /* Replication */
    if (allsections || defsections || !strcasecmp(section,"replication")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Replication\r\n"
            "role:%s\r\n",
            server.masterhost == NULL ? "master" : "slave");
        if (server.masterhost) {
            info = sdscatprintf(info,
                "master_host:%s\r\n"
                "master_port:%d\r\n"
                "master_link_status:%s\r\n"
                "master_last_io_seconds_ago:%d\r\n"
                "master_sync_in_progress:%d\r\n"
                ,server.masterhost,
                server.masterport,
                (server.repl_state == REDIS_REPL_CONNECTED) ?
                    "up" : "down",
                server.master ?
                ((int)(server.unixtime-server.master->lastinteraction)) : -1,
                server.repl_state == REDIS_REPL_TRANSFER
            );

            if (server.repl_state == REDIS_REPL_TRANSFER) {
                info = sdscatprintf(info,
                    "master_sync_left_bytes:%ld\r\n"
                    "master_sync_last_io_seconds_ago:%d\r\n"
                    ,(long)server.repl_transfer_left,
                    (int)(server.unixtime-server.repl_transfer_lastio)
                );
            }

            if (server.repl_state != REDIS_REPL_CONNECTED) {
                info = sdscatprintf(info,
                    "master_link_down_since_seconds:%ld\r\n",
                    (long)server.unixtime-server.repl_down_since);
            }
        }
        info = sdscatprintf(info,
            "connected_slaves:%lu\r\n",
            listLength(server.slaves));
        if (listLength(server.slaves)) {
            int slaveid = 0;
            listNode *ln;
            listIter li;

            listRewind(server.slaves,&li);
            while((ln = listNext(&li))) {
                redisClient *slave = listNodeValue(ln);
                char *state = NULL;
                char ip[32];
                int port;

                if (anetPeerToString(slave->fd,ip,&port) == -1) continue;
                switch(slave->replstate) {
                case REDIS_REPL_WAIT_BGSAVE_START:
                case REDIS_REPL_WAIT_BGSAVE_END:
                    state = "wait_bgsave";
                    break;
                case REDIS_REPL_SEND_BULK:
                    state = "send_bulk";
                    break;
                case REDIS_REPL_ONLINE:
                    state = "online";
                    break;
                }
                if (state == NULL) continue;
                info = sdscatprintf(info,"slave%d:%s,%d,%s\r\n",
                    slaveid,ip,port,state);
                slaveid++;
            }
        }
    }

    /* CPU */
    if (allsections || defsections || !strcasecmp(section,"cpu")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
        "# CPU\r\n"
        "used_cpu_sys:%.2f\r\n"
        "used_cpu_user:%.2f\r\n"
        "used_cpu_sys_children:%.2f\r\n"
        "used_cpu_user_children:%.2f\r\n",
        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000);
    }

    /* cmdtime */
    if (allsections || !strcasecmp(section,"commandstats")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info, "# Commandstats\r\n");
        numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
        for (j = 0; j < numcommands; j++) {
            struct redisCommand *c = redisCommandTable+j;

            if (!c->calls) continue;
            info = sdscatprintf(info,
                "cmdstat_%s:calls=%lld,usec=%lld,usec_per_call=%.2f\r\n",
                c->name, c->calls, c->microseconds,
                (c->calls == 0) ? 0 : ((float)c->microseconds/c->calls));
        }
    }

    /* Clusetr */
    if (allsections || defsections || !strcasecmp(section,"cluster")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
        "# Cluster\r\n"
        "cluster_enabled:%d\r\n",
        server.cluster_enabled);
    }

    /* Key space */
    if (allsections || defsections || !strcasecmp(section,"keyspace")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info, "# Keyspace\r\n");
        for (j = 0; j < server.dbnum; j++) {
            long long keys, vkeys;

            keys = dictSize(server.db[j].dict);
            vkeys = dictSize(server.db[j].expires);
            if (keys || vkeys) {
                info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
                    j, keys, vkeys);
            }
        }
    }
    return info;
}