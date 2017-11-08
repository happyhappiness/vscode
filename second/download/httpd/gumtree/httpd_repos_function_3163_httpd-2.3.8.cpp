static int make_child(server_rec * s, int slot)
{
    int pid;

    if (slot + 1 > max_daemons_limit) {
        max_daemons_limit = slot + 1;
    }

    if (one_process) {
        set_signals();
        ap_scoreboard_image->parent[slot].pid = getpid();
        child_main(slot);
    }

    if ((pid = fork()) == -1) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, s,
                     "fork: Unable to fork new process");

        /* fork didn't succeed.  There's no need to touch the scoreboard;
         * if we were trying to replace a failed child process, then
         * server_main_loop() marked its workers SERVER_DEAD, and if
         * we were trying to replace a child process that exited normally,
         * its worker_thread()s left SERVER_DEAD or SERVER_GRACEFUL behind.
         */

        /* In case system resources are maxxed out, we don't want
           Apache running away with the CPU trying to fork over and
           over and over again. */
        apr_sleep(apr_time_from_sec(10));

        return -1;
    }

    if (!pid) {
#ifdef HAVE_BINDPROCESSOR
        /* By default, AIX binds to a single processor.  This bit unbinds
         * children which will then bind to another CPU.
         */
        int status = bindprocessor(BINDPROCESS, (int) getpid(),
                                   PROCESSOR_CLASS_ANY);
        if (status != OK)
            ap_log_error(APLOG_MARK, APLOG_DEBUG, errno,
                         ap_server_conf,
                         "processor unbind failed");
#endif
        RAISE_SIGSTOP(MAKE_CHILD);

        apr_signal(SIGTERM, just_die);
        child_main(slot);

        clean_child_exit(0);
    }
    /* else */
    if (ap_scoreboard_image->parent[slot].pid != 0) {
        /* This new child process is squatting on the scoreboard
         * entry owned by an exiting child process, which cannot
         * exit until all active requests complete.
         * Don't forget about this exiting child process, or we
         * won't be able to kill it if it doesn't exit by the
         * time the server is shut down.
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                     "taking over scoreboard slot from %" APR_PID_T_FMT "%s",
                     ap_scoreboard_image->parent[slot].pid,
                     ap_scoreboard_image->parent[slot].quiescing ?
                         " (quiescing)" : "");
        ap_register_extra_mpm_process(ap_scoreboard_image->parent[slot].pid);
    }
    ap_scoreboard_image->parent[slot].quiescing = 0;
    ap_scoreboard_image->parent[slot].pid = pid;
    return 0;
}