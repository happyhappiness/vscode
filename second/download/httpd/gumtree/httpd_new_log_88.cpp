ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO,
				 server_conf,
				 "httpd: removed PID file %s (pid=%ld)",
				 pidfile, (long)getpid());