	     * Kill child processes, tell them to call child_exit, etc...

	     */

	    if (ap_killpg(pgrp, SIGTERM) < 0) {

		ap_log_error(APLOG_MARK, APLOG_WARNING, server_conf, "killpg SIGTERM");

	    }

	    reclaim_child_processes(1);		/* Start with SIGTERM */



	    /* cleanup pid file on normal shutdown */

	    {

		const char *pidfile = NULL;

		pidfile = ap_server_root_relative (pconf, ap_pid_fname);

		if ( pidfile != NULL && unlink(pidfile) == 0)

		    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,

				 server_conf,

				 "httpd: removed PID file %s (pid=%ld)",

				 pidfile, (long)getpid());

	    }



	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, server_conf,

			"httpd: caught SIGTERM, shutting down");

	    clean_parent_exit(0);

	}



	/* we've been told to restart */

	signal(SIGHUP, SIG_IGN);

	signal(SIGUSR1, SIG_IGN);

