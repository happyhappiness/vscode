
static void just_die(int sig)
{
    clean_child_exit(0);
}

/* volatile because they're updated from a signal handler */
static int volatile shutdown_pending;
static int volatile restart_pending;
static int volatile die_now = 0;

static void stop_listening(int sig)
{
    mpm_state = AP_MPMQ_STOPPING;
    ap_close_listeners_ex(my_bucket->listeners);

    /* For a graceful stop, we want the child to exit when done */
    die_now = 1;
}

static void sig_term(int sig)
{
    if (shutdown_pending == 1) {
        /* Um, is this _probably_ not an error, if the user has
         * tried to do a shutdown twice quickly, so we won't
         * worry about reporting it.
         */
        return;
    }
    mpm_state = AP_MPMQ_STOPPING;
    shutdown_pending = 1;
    retained->is_graceful = (sig == AP_SIG_GRACEFUL_STOP);
}

/* restart() is the signal handler for SIGHUP and AP_SIG_GRACEFUL
 * in the parent process, unless running in ONE_PROCESS mode
 */
static void restart(int sig)
{
    if (restart_pending == 1) {
        /* Probably not an error - don't bother reporting it */
        return;
    }
    mpm_state = AP_MPMQ_STOPPING;
    restart_pending = 1;
    retained->is_graceful = (sig == AP_SIG_GRACEFUL);
}

static void set_signals(void)
{
#ifndef NO_USE_SIGACTION
    struct sigaction sa;
#endif

    if (!one_process) {
        ap_fatal_signal_setup(ap_server_conf, pconf);
    }

#ifndef NO_USE_SIGACTION
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sa.sa_handler = sig_term;
    if (sigaction(SIGTERM, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00147) "sigaction(SIGTERM)");
#ifdef AP_SIG_GRACEFUL_STOP
    if (sigaction(AP_SIG_GRACEFUL_STOP, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00148)
                     "sigaction(" AP_SIG_GRACEFUL_STOP_STRING ")");
#endif
#ifdef SIGINT
    if (sigaction(SIGINT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00149) "sigaction(SIGINT)");
#endif
#ifdef SIGXCPU
    sa.sa_handler = SIG_DFL;
    if (sigaction(SIGXCPU, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00150) "sigaction(SIGXCPU)");
#endif
#ifdef SIGXFSZ
    /* For systems following the LFS standard, ignoring SIGXFSZ allows
     * a write() beyond the 2GB limit to fail gracefully with E2BIG
     * rather than terminate the process. */
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGXFSZ, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00151) "sigaction(SIGXFSZ)");
#endif
#ifdef SIGPIPE
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00152) "sigaction(SIGPIPE)");
#endif

    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy
     * processing one
     */
    sigaddset(&sa.sa_mask, SIGHUP);
    sigaddset(&sa.sa_mask, AP_SIG_GRACEFUL);
    sa.sa_handler = restart;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00153) "sigaction(SIGHUP)");
    if (sigaction(AP_SIG_GRACEFUL, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00154) "sigaction(" AP_SIG_GRACEFUL_STRING ")");
#else
    if (!one_process) {
#ifdef SIGXCPU
        apr_signal(SIGXCPU, SIG_DFL);
#endif /* SIGXCPU */
#ifdef SIGXFSZ
        apr_signal(SIGXFSZ, SIG_IGN);
#endif /* SIGXFSZ */
    }

    apr_signal(SIGTERM, sig_term);
#ifdef SIGHUP
    apr_signal(SIGHUP, restart);
#endif /* SIGHUP */
#ifdef AP_SIG_GRACEFUL
    apr_signal(AP_SIG_GRACEFUL, restart);
#endif /* AP_SIG_GRACEFUL */
#ifdef AP_SIG_GRACEFUL_STOP
    apr_signal(AP_SIG_GRACEFUL_STOP, sig_term);
#endif /* AP_SIG_GRACEFUL */
#ifdef SIGPIPE
    apr_signal(SIGPIPE, SIG_IGN);
#endif /* SIGPIPE */

#endif
}

/*****************************************************************
 * Child process main loop.
 * The following vars are static to avoid getting clobbered by longjmp();
 * they are really private to child_main.
 */

