void ap_relieve_child_processes(void)
{
    int i;
    extra_process_t *cur_extra;
    int max_daemons;

    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);

    /* now see who is done */
    for (i = 0; i < max_daemons; ++i) {
        pid_t pid = MPM_CHILD_PID(i);

        if (pid == 0) {
            continue; /* not every scoreboard entry is in use */
        }

        if (reclaim_one_pid(pid, DO_NOTHING)) {
            MPM_NOTE_CHILD_KILLED(i);
        }
    }

    cur_extra = extras;
    while (cur_extra) {
        extra_process_t *next = cur_extra->next;

        if (reclaim_one_pid(cur_extra->pid, DO_NOTHING)) {
            AP_DEBUG_ASSERT(1 == ap_unregister_extra_mpm_process(cur_extra->pid));
        }
        cur_extra = next;
    }
}