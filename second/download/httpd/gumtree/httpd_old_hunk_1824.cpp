    }

    if (stat != APR_SUCCESS) {
        /* For all intents and purposes, this is impossibly unlikely,
         * but APR doesn't exist yet, we can't use it for reporting
         * these earliest two failures;
         */
        char ctimebuff[APR_CTIME_LEN];
        apr_ctime(ctimebuff, apr_time_now());
        fprintf(stderr, "[%s] [crit] (%d) %s: %s failed "
                        "to initial context, exiting\n", 
                        ctimebuff, stat, (*argv)[0], failed);
        apr_terminate();
        exit(1);
    }

    apr_pool_tag(cntx, "process");
    ap_open_stderr_log(cntx);

    /* Now we have initialized apr and our logger, no more
     * exceptional error reporting required for the lifetime
     * of this server process.
