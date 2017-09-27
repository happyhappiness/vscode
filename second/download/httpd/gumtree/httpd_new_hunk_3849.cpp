
    if (retained->is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00171)
                    "Graceful restart requested, doing restart");

        /* kill off the idle ones */
        for (i = 0; i < num_buckets; i++) {
            ap_mpm_pod_killpg(all_buckets[i].pod, retained->max_daemons_limit);
        }

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.  This will break
         * in a very nasty way if we ever have the scoreboard totally
         * file-based (no shared memory)
         */
