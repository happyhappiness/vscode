        case AP_MPMQ_MAX_REQUESTS_DAEMON:
            *result = ap_max_requests_per_child;
            return APR_SUCCESS;
        case AP_MPMQ_MAX_DAEMONS:
            *result = ap_daemons_limit;
            return APR_SUCCESS;
    }
    return APR_ENOTIMPL;
}

/* a clean exit from a child with proper cleanup */ 
static void clean_child_exit(int code) __attribute__ ((noreturn));
static void clean_child_exit(int code)
{
    if (pchild) {
        apr_pool_destroy(pchild);
    }
    exit(code);
}

/* handle all varieties of core dumping signals */
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

static void just_die(int sig)
{
    clean_child_exit(0);
}

/*****************************************************************
