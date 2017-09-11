                long long now = ustime();
                size_t frag_bytes;
                float frag_pct = getAllocatorFragmentation(&frag_bytes);
                serverLog(LL_VERBOSE,
                    "Active defrag done in %dms, reallocated=%d, frag=%.0f%%, frag_bytes=%zu",
                    (int)((now - start_scan)/1000), (int)(server.stat_active_defrag_hits - start_stat), frag_pct, frag_bytes);

