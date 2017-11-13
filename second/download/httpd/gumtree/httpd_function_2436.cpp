static void sig_coredump(int sig)
{
    apr_filepath_set(ap_coredump_dir, pconf);
    apr_signal(sig, SIG_DFL);
#if AP_ENABLE_EXCEPTION_HOOK
    run_fatal_exception_hook(sig);
#endif
    /* linuxthreads issue calling getpid() here:
     *   This comparison won't match if the crashing thread is
     *   some module's thread that runs in the parent process.
     *   The fallout, which is limited to linuxthreads:
     *   The special log message won't be written when such a
     *   thread in the parent causes the parent to crash.
     */
    if (getpid() == parent_pid) {
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
    kill(getpid(), sig);
    /* At this point we've got sig blocked, because we're still inside
     * the signal handler.  When we leave the signal handler it will
     * be unblocked, and we'll take the signal... and coredump or whatever
     * is appropriate for this particular Unix.  In addition the parent
     * will see the real signal we received -- whereas if we called
     * abort() here, the parent would only see SIGABRT.
     */
}