report = sdscatprintf(report,
            "%d. %s: %d latency spikes (average %lums, mean deviation %lums, period %lu sec). Worst all time event %lums.",
            eventnum, event,
            ls.samples,
            (unsigned long) ls.avg,
            (unsigned long) ls.mad,
            (unsigned long) ls.period/ls.samples,
            (unsigned long) ts->max);