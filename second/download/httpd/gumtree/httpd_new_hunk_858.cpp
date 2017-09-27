	 * it will say SERVER_STARTING forever and ever
	 */
	(void) ap_update_child_status_from_indexes(slot, 0, SERVER_DEAD,
                                                   (request_rec *) NULL);

	/* In case system resources are maxxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again.
         */
	sleep(10);

	return -1;
    }

    if (!pid) {
#ifdef HAVE_BINDPROCESSOR
        /* by default AIX binds to a single processor
         * this bit unbinds children which will then bind to another cpu
         */
        int status = bindprocessor(BINDPROCESS, (int)getpid(),
				   PROCESSOR_CLASS_ANY);
	if (status != OK) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno,
                         ap_server_conf, "processor unbind failed %d", status);
	}
#endif
	RAISE_SIGSTOP(MAKE_CHILD);
        AP_MONCONTROL(1);
        /* Disable the parent's signal handlers and set up proper handling in
         * the child.
	 */
	apr_signal(SIGHUP, just_die);
	apr_signal(SIGTERM, just_die);
        /* The child process just closes listeners on AP_SIG_GRACEFUL.
         * The pod is used for signalling the graceful restart.
         */
        apr_signal(AP_SIG_GRACEFUL, stop_listening);
	child_main(slot);
    }

    ap_scoreboard_image->parent[slot].pid = pid;

    return 0;
