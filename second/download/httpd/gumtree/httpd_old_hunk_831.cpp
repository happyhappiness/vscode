 * assume means something serious is wrong (which it will be, for the
 * child to force an exit) and so do an exit anyway.
 */

static void ap_start_shutdown(void)
{
    mpm_state = AP_MPMQ_STOPPING;
 
    if (shutdown_pending == 1) {
	/* Um, is this _probably_ not an error, if the user has
	 * tried to do a shutdown twice quickly, so we won't
	 * worry about reporting it.
	 */
	return;
    }
    shutdown_pending = 1;
}

/* do a graceful restart if graceful == 1 */
static void ap_start_restart(int graceful)
{
    mpm_state = AP_MPMQ_STOPPING;

    if (restart_pending == 1) {
        /* Probably not an error - don't bother reporting it */
        return;
    }
    restart_pending = 1;
    is_graceful = graceful;
}

static void sig_term(int sig)
{
    ap_start_shutdown();
}

static void restart(int sig)
{
    ap_start_restart(sig == AP_SIG_GRACEFUL);
}

static void tell_workers_to_exit(void)
{
    apr_size_t len;
    int i = 0;

    mpm_state = AP_MPMQ_STOPPING;

    for (i = 0 ; i < ap_max_child_assigned; i++){
        len = 4;
        if (apr_sendto(udp_sock, udp_sa, 0, "die!", &len) != APR_SUCCESS)
            break;
    }   
}

static void set_signals(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (!one_process) {
	sa.sa_handler = sig_coredump;

	if (sigaction(SIGSEGV, &sa, NULL) < 0)
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGSEGV)");
	if (sigaction(SIGBUS, &sa, NULL) < 0)
