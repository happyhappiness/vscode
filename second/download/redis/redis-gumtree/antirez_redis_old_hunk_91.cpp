    long long start, timelimit;

    if (server.aof_child_pid!=-1 || server.rdb_child_pid!=-1)
        return; /* defragging memory while there's a fork will just do damage. */

    /* once a second, check if we the fragmentation justfies starting a scan or making it more aggressive */
    run_with_period(1000) {
        size_t frag_bytes;
        float frag_pct = getAllocatorFragmentation(&frag_bytes);
        /* if we're not already running, and below the threshold, exit. */
        if (!server.active_defrag_running) {
            if(frag_pct < server.active_defrag_threshold_lower || frag_bytes < server.active_defrag_ignore_bytes)
                return;
        }

        /* calculate the adaptive aggressiveness of the defrag */
        int cpu_pct = INTERPOLATE(frag_pct, server.active_defrag_threshold_lower, server.active_defrag_threshold_upper,
                                  server.active_defrag_cycle_min, server.active_defrag_cycle_max);
        cpu_pct = LIMIT(cpu_pct, server.active_defrag_cycle_min, server.active_defrag_cycle_max);
         /* we allow increasing the aggressiveness during a scan, but don't reduce it */
        if (!server.active_defrag_running || cpu_pct > server.active_defrag_running) {
            server.active_defrag_running = cpu_pct;
            serverLog(LL_VERBOSE,
                "Starting active defrag, frag=%.0f%%, frag_bytes=%zu, cpu=%d%%",
