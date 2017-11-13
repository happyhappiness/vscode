static void sig_coredump(int sig)
{
    chdir(ap_coredump_dir);
    apr_signal(sig, SIG_DFL);
    if (ap_my_pid == parent_pid) {
            ap_log_error(APLOG_MARK, APLOG_NOTICE,
                         0, ap_server_conf,
                         "seg fault or similar nasty error detected "
                         "in the parent process");
    }
    kill(getpid(), sig);
    /* At this point we've got sig blocked, because we're still inside
     * the signal handler.  When we leave the signal handler it will
     * be unblocked, and we'll take the signal... and coredump or whatever
     * is appropriate for this particular Unix.  In addition the parent
     * will see the real signal we received -- whereas if we called
     * abort() here, the parent would only see SIGABRT.
     */
}