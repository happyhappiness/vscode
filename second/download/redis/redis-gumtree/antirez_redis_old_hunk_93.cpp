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
                frag_pct, frag_bytes, cpu_pct);
        }
    }
