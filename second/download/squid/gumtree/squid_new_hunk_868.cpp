                      stats.ms_bytes_total / 1024);

    storeAppendPrintf(sentry, "\tTotal free:            %6.0f KB %.0f%%\n",
                      stats.ms_bytes_free / 1024,
                      Math::doublePercent(stats.ms_bytes_free, stats.ms_bytes_total));

#endif

    storeAppendPrintf(sentry, "Memory accounted for:\n");
    storeAppendPrintf(sentry, "\tTotal accounted:       %6.0f KB\n",
                      stats.total_accounted / 1024);
    {
        MemPoolGlobalStats mp_stats;
        memPoolGetGlobalStats(&mp_stats);
        storeAppendPrintf(sentry, "\tmemPoolAlloc calls: %9.0f\n",
                          stats.gb_saved_count);
        storeAppendPrintf(sentry, "\tmemPoolFree calls:  %9.0f\n",
                          stats.gb_freed_count);
    }

