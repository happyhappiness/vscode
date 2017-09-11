        analyzeLatencyForEvent(event,&ls);

        report = sdscatprintf(report,
            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %.2f sec). Worst all time event %lums.",
            eventnum, event,
            ls.samples,
            (unsigned long) ls.avg,
            (unsigned long) ls.mad,
            (double) ls.period/ls.samples,
            (unsigned long) ts->max);

        /* Add some event specific information. */
