        /* by default AIX binds to a single processor
         * this bit unbinds children which will then bind to another cpu
         */
	int status = bindprocessor(BINDPROCESS, (int)getpid(), 
				   PROCESSOR_CLASS_ANY);
	if (status != OK) {
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, errno, 
                         ap_server_conf, "processor unbind failed %d", status);
	}
#endif
	RAISE_SIGSTOP(MAKE_CHILD);
        AP_MONCONTROL(1);
        /* Disable the parent's signal handlers and set up proper handling in
