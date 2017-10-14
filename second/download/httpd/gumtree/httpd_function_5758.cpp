static int event_open_logs(apr_pool_t * p, apr_pool_t * plog,
                           apr_pool_t * ptemp, server_rec * s)
{
    int startup = 0;
    int level_flags = 0;
    int num_buckets = 0;
    ap_listen_rec **listen_buckets;
    apr_status_t rv;
    int i;

    pconf = p;

    /* the reverse of pre_config, we want this only the first time around */
    if (retained->module_loads == 1) {
        startup = 1;
        level_flags |= APLOG_STARTUP;
    }

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
                     (startup ? NULL : s),
                     "no listening sockets available, shutting down");
        return DONE;
    }

    if (one_process) {
        num_buckets = 1;
    }
    else if (retained->is_graceful) {
        /* Preserve the number of buckets on graceful restarts. */
        num_buckets = retained->num_buckets;
    }
    if ((rv = ap_duplicate_listeners(pconf, ap_server_conf,
                                     &listen_buckets, &num_buckets))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                     (startup ? NULL : s),
                     "could not duplicate listeners");
        return DONE;
    }

    all_buckets = apr_pcalloc(pconf, num_buckets * sizeof(*all_buckets));
    for (i = 0; i < num_buckets; i++) {
        if (!one_process && /* no POD in one_process mode */
                (rv = ap_mpm_podx_open(pconf, &all_buckets[i].pod))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                         (startup ? NULL : s),
                         "could not open pipe-of-death");
            return DONE;
        }
        all_buckets[i].listeners = listen_buckets[i];
    }

    if (retained->max_buckets < num_buckets) {
        int new_max, *new_ptr;
        new_max = retained->max_buckets * 2;
        if (new_max < num_buckets) {
            new_max = num_buckets;
        }
        new_ptr = (int *)apr_palloc(ap_pglobal, new_max * sizeof(int));
        memcpy(new_ptr, retained->idle_spawn_rate,
               retained->num_buckets * sizeof(int));
        retained->idle_spawn_rate = new_ptr;
        retained->max_buckets = new_max;
    }
    if (retained->num_buckets < num_buckets) {
        int rate_max = 1;
        /* If new buckets are added, set their idle spawn rate to
         * the highest so far, so that they get filled as quickly
         * as the existing ones.
         */
        for (i = 0; i < retained->num_buckets; i++) {
            if (rate_max < retained->idle_spawn_rate[i]) {
                rate_max = retained->idle_spawn_rate[i];
            }
        }
        for (/* up to date i */; i < num_buckets; i++) {
            retained->idle_spawn_rate[i] = rate_max;
        }
    }
    retained->num_buckets = num_buckets;

    /* for skiplist */
    srand((unsigned int)apr_time_now());
    return OK;
}