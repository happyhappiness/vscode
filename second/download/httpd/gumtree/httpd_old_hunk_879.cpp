                     "ignored during restart");
        changed_limit_at_restart = 0;
    }

    ap_server_conf = s;

    /* Initialize cross-process accept lock */
    ap_lock_fname = apr_psprintf(_pconf, "%s.%u",
                                 ap_server_root_relative(_pconf, ap_lock_fname),
                                 my_pid);
    rv = SAFE_ACCEPT(apr_proc_mutex_create(&process_accept_mutex,
                                     ap_lock_fname, ap_accept_lock_mech,
