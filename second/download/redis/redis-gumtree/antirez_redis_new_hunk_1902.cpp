            (double) ls.period/ls.samples,
            (unsigned long) ts->max);

        /* Fork */
        if (!strcasecmp(event,"fork")) {
            char *fork_quality;
            if (server.stat_fork_rate < 10) {
                fork_quality = "terrible";
                advise_better_vm = 1;
                advices++;
            } else if (server.stat_fork_rate < 25) {
                fork_quality = "poor";
                advise_better_vm = 1;
                advices++;
            } else if (server.stat_fork_rate < 100) {
                fork_quality = "good";
            } else {
                fork_quality = "excellent";
            }
            report = sdscatprintf(report,
                " Fork rate is %.2f GB/sec (%s).", server.stat_fork_rate,
                fork_quality);
        }

        /* Potentially commands. */
        if (!strcasecmp(event,"command")) {
            if (server.slowlog_log_slower_than == 0) {
                advise_slowlog_enabled = 1;
                advices++;
            } else if (server.slowlog_log_slower_than/1000 >
                       server.latency_monitor_threshold)
            {
                advise_slowlog_tuning = 1;
                advices++;
            }
            advise_slowlog_inspect = 1;
            advise_large_objects = 1;
            advices += 2;
        }

        /* fast-command. */
        if (!strcasecmp(event,"fast-command")) {
            advise_scheduler = 1;
            advices++;
        }

        /* AOF and I/O. */
        if (!strcasecmp(event,"aof-write-pending-fsync")) {
            advise_local_disk = 1;
            advise_disk_contention = 1;
            advise_ssd = 1;
            advise_data_writeback = 1;
            advices += 4;
        }

        if (!strcasecmp(event,"aof-write-active-child")) {
            advise_no_appendfsync = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advices += 3;
        }

        if (!strcasecmp(event,"aof-write-alone")) {
            advise_local_disk = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advices += 3;
        }

        if (!strcasecmp(event,"aof-fsync-always")) {
            advise_relax_fsync_policy = 1;
            advices++;
        }

        if (!strcasecmp(event,"aof-fstat") ||
            !strcasecmp(event,"rdb-unlik-temp-file")) {
            advise_disk_contention = 1;
            advise_local_disk = 1;
            advices += 2;
        }

        if (!strcasecmp(event,"aof-rewrite-diff-write") ||
            !strcasecmp(event,"aof-rename")) {
            advise_write_load_info = 1;
            advise_data_writeback = 1;
            advise_ssd = 1;
            advise_local_disk = 1;
            advices += 4;
        }

        /* Expire cycle. */
        if (!strcasecmp(event,"expire-cycle")) {
            advise_hz = 1;
            advise_large_objects = 1;
            advices += 2;
        }

        /* Eviction cycle. */
        if (!strcasecmp(event,"eviction-cycle")) {
            advise_large_objects = 1;
            advices++;
        }

        report = sdscatlen(report,"\n",1);
