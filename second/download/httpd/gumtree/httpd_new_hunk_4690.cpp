        return !OK;
    }

    if (one_process) {
        num_buckets = 1;
    }
    else if (retained->mpm->was_graceful) {
        /* Preserve the number of buckets on graceful restarts. */
        num_buckets = retained->mpm->num_buckets;
    }
    if ((rv = ap_duplicate_listeners(pconf, ap_server_conf,
                                     &listen_buckets, &num_buckets))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                     (startup ? NULL : s),
                     "could not duplicate listeners");
