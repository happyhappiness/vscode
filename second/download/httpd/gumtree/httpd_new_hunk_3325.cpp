}

static int make_child(server_rec * s, int slot)
{
    int pid;

    if (slot + 1 > retained->max_daemons_limit) {
        retained->max_daemons_limit = slot + 1;
    }

    if (one_process) {
        set_signals();
        event_note_child_started(slot, getpid());
        child_main(slot);
        /* NOTREACHED */
    }

    if ((pid = fork()) == -1) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, s, APLOGNO(00481)
                     "fork: Unable to fork new process");

        /* fork didn't succeed.  There's no need to touch the scoreboard;
         * if we were trying to replace a failed child process, then
         * server_main_loop() marked its workers SERVER_DEAD, and if
         * we were trying to replace a child process that exited normally,
