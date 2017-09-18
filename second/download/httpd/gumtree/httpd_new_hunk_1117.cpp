    ap_max_mem_free = (apr_uint32_t)value * 1024;

    return NULL;
}

#endif /* AP_MPM_WANT_SET_MAX_MEM_FREE */

#ifdef AP_MPM_WANT_FATAL_SIGNAL_HANDLER

static pid_t parent_pid, my_pid;
apr_pool_t *pconf;

#if AP_ENABLE_EXCEPTION_HOOK

static int exception_hook_enabled;

const char *ap_mpm_set_exception_hook(cmd_parms *cmd, void *dummy,
                                      const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (cmd->server->is_virtual) {
	return "EnableExceptionHook directive not allowed in <VirtualHost>";
    }

    if (strcasecmp(arg, "on") == 0) {
        exception_hook_enabled = 1;
    }
    else if (strcasecmp(arg, "off") == 0) {
        exception_hook_enabled = 0;
    }
    else {
        return "parameter must be 'on' or 'off'";
    }

    return NULL;
}

APR_HOOK_STRUCT(
    APR_HOOK_LINK(fatal_exception)
)

AP_IMPLEMENT_HOOK_RUN_ALL(int, fatal_exception,
                          (ap_exception_info_t *ei), (ei), OK, DECLINED)

static void run_fatal_exception_hook(int sig)
{
    ap_exception_info_t ei = {0};

    if (exception_hook_enabled &&
        geteuid() != 0 && 
        my_pid != parent_pid) {
        ei.sig = sig;
        ei.pid = my_pid;
        ap_run_fatal_exception(&ei);
    }
}
#endif /* AP_ENABLE_EXCEPTION_HOOK */

/* handle all varieties of core dumping signals */
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

apr_status_t ap_fatal_signal_child_setup(server_rec *s)
{
    my_pid = getpid();
    return APR_SUCCESS;
}

apr_status_t ap_fatal_signal_setup(server_rec *s, apr_pool_t *in_pconf)
{
#ifndef NO_USE_SIGACTION
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    
#if defined(SA_ONESHOT)
    sa.sa_flags = SA_ONESHOT;
#elif defined(SA_RESETHAND)
    sa.sa_flags = SA_RESETHAND;
#else
    sa.sa_flags = 0;
#endif

    sa.sa_handler = sig_coredump;
    if (sigaction(SIGSEGV, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGSEGV)");
#ifdef SIGBUS
    if (sigaction(SIGBUS, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGBUS)");
#endif
#ifdef SIGABORT
    if (sigaction(SIGABORT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABORT)");
#endif
#ifdef SIGABRT
    if (sigaction(SIGABRT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABRT)");
#endif
#ifdef SIGILL
    if (sigaction(SIGILL, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGILL)");
#endif

#else /* NO_USE_SIGACTION */
    
    apr_signal(SIGSEGV, sig_coredump);
#ifdef SIGBUS
    apr_signal(SIGBUS, sig_coredump);
#endif /* SIGBUS */
#ifdef SIGABORT
    apr_signal(SIGABORT, sig_coredump);
#endif /* SIGABORT */
#ifdef SIGABRT
    apr_signal(SIGABRT, sig_coredump);
#endif /* SIGABRT */
#ifdef SIGILL
    apr_signal(SIGILL, sig_coredump);
#endif /* SIGILL */

#endif /* NO_USE_SIGACTION */

    pconf = in_pconf;
    parent_pid = my_pid = getpid();

    return APR_SUCCESS;
}

#endif /* AP_MPM_WANT_FATAL_SIGNAL_HANDLER */
