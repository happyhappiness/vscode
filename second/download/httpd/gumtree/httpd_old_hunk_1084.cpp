    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
		"AcceptMutex: %s (default: %s)",
		apr_proc_mutex_name(accept_mutex),
		apr_proc_mutex_defname());
#endif
    restart_pending = shutdown_pending = 0;

    server_main_loop(remaining_children_to_start);

    if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         * (By "gracefully" we don't mean graceful in the same sense as 
         * "apachectl graceful" where we allow old connections to finish.)
