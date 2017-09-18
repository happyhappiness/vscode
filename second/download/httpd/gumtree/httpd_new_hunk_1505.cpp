	ap_log_error(APLOG_MARK,APLOG_ERR|APLOG_NOERRNO, server_conf,
 	    "forcing termination of child #%d (handle %d)", i, process_handles[i]);
	TerminateProcess((HANDLE) process_handles[i], 1);
    }
    service_set_status(SERVICE_STOPPED);

    /* cleanup pid file on normal shutdown */
    {
	const char *pidfile = NULL;
	pidfile = ap_server_root_relative (pparent, ap_pid_fname);
	if ( pidfile != NULL && unlink(pidfile) == 0)
	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
			 server_conf,
			 "httpd: removed PID file %s (pid=%ld)",
			 pidfile, (long)getpid());
    }

    if (pparent) {
	ap_destroy_pool(pparent);
    }

    ap_destroy_mutex(start_mutex);
    return (0);
