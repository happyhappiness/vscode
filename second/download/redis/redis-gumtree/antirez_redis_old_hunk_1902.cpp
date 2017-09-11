            (double) ls.period/ls.samples,
            (unsigned long) ts->max);

        /* Add some event specific information. */
        nontrivial = ts->max > 100;
        severe = ts->max > 500;

        /* Fork */
        if (!strcasecmp(event,"fork")) {
            double fork_bandwidth = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024); /* GB per second. */
        }

        report = sdscatlen(report,"\n",1);
