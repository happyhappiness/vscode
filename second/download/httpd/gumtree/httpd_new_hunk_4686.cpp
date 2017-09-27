    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00294)
                "Accept mutex: %s (default: %s)",
                (all_buckets[0].mutex)
                    ? apr_proc_mutex_name(all_buckets[0].mutex)
                    : "none",
                apr_proc_mutex_defname());
    retained->mpm->mpm_state = AP_MPMQ_RUNNING;

    server_main_loop(remaining_children_to_start, num_buckets);
    retained->mpm->mpm_state = AP_MPMQ_STOPPING;

    if (retained->mpm->shutdown_pending && retained->mpm->is_ungraceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        for (i = 0; i < num_buckets; i++) {
            ap_mpm_podx_killpg(all_buckets[i].pod, ap_daemons_limit,
                               AP_MPM_PODX_RESTART);
