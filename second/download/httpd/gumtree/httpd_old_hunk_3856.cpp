
    free(threads);

    clean_child_exit(resource_shortage ? APEXIT_CHILDSICK : 0);
}

static int make_child(server_rec *s, int slot)
{
    int pid;

    if (slot + 1 > retained->max_daemons_limit) {
        retained->max_daemons_limit = slot + 1;
    }

    if (one_process) {
        set_signals();
        worker_note_child_started(slot, getpid());
        child_main(slot);
        /* NOTREACHED */
    }

    if ((pid = fork()) == -1) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, s, APLOGNO(00283)
                     "fork: Unable to fork new process");
        /* fork didn't succeed.  There's no need to touch the scoreboard;
