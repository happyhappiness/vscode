        ap_reclaim_child_processes(1, event_note_child_killed);

        return DONE;
    }

    /* we've been told to restart */
    if (one_process) {
        /* not worth thinking about */
        return DONE;
    }

    /* advance to the next generation */
    /* XXX: we really need to make sure this new generation number isn't in
     * use by any of the children.
     */
    ++retained->mpm->my_generation;
    ap_scoreboard_image->global->running_generation = retained->mpm->my_generation;

    if (!retained->mpm->is_ungraceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00493)
                     AP_SIG_GRACEFUL_STRING
                     " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        for (i = 0; i < num_buckets; i++) {
            ap_mpm_podx_killpg(all_buckets[i].pod, active_daemons_limit,
