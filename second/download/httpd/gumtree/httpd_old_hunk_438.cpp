
    ap_log_pid(pconf, ap_pid_fname);

    first_server_limit = server_limit;
    first_thread_limit = thread_limit;
    if (changed_limit_at_restart) {
        ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_NOERRNO, 0, s,
                     "WARNING: Attempt to change ServerLimit or ThreadLimit "
                     "ignored during restart");
        changed_limit_at_restart = 0;
    }
    
    /* Initialize cross-process accept lock */
