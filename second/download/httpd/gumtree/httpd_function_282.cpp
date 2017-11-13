static void sig_coredump(int sig)
{
    apr_filepath_set(ap_coredump_dir, pconf);
    apr_signal(sig, SIG_DFL);
    if (ap_my_pid == parent_pid) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE,
                     0, ap_server_conf,
                     "seg fault or similar nasty error detected "
                     "in the parent process");
        
        /* XXX we can probably add some rudimentary cleanup code here,
         * like getting rid of the pid file.  If any additional bad stuff
         * happens, we are protected from recursive errors taking down the
         * system since this function is no longer the signal handler   GLA
         */
    }
    kill(ap_my_pid, sig);
    /* At this point we've got sig blocked, because we're still inside
     * the signal handler.  When we leave the signal handler it will
     * be unblocked, and we'll take the signal... and coredump or whatever
     * is appropriate for this particular Unix.  In addition the parent
     * will see the real signal we received -- whereas if we called
     * abort() here, the parent would only see SIGABRT.
     */
}