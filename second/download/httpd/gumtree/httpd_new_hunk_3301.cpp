         * (if they relied on global pools or mutexes, for example) then
         * the datestamp logic will need to be replaced.
         */
        char ctimebuff[APR_CTIME_LEN];
        apr_ctime(ctimebuff, apr_time_now());
        fprintf(stderr, "[%s] [crit] (%d) %s: %s failed "
                        "to initial context, exiting\n",
                        ctimebuff, stat, (*argv)[0], failed);
        apr_terminate();
        exit(1);
    }

    apr_pool_abort_set(abort_on_oom, cntx);
