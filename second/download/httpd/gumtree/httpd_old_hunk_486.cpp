        /* XXX if (!ps->quiescing)     is probably more reliable  GLA */
        if (!any_dying_threads) {
            last_non_dead = i;
            ++total_non_dead;
        }
    }
    ap_max_daemons_limit = last_non_dead + 1;

    if (idle_thread_count > max_spare_threads) {
        /* Kill off one child */
        ap_mpm_pod_signal(pod, TRUE);
        idle_spawn_rate = 1;
