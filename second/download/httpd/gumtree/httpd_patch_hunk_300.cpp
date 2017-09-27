     shutdown_pending = os_check_server(tpf_server_name);
     ap_check_signals();
     sleep(1);
 #endif /*TPF */
     }
 
+    mpm_state = AP_MPMQ_STOPPING;
+
     if (shutdown_pending) {
 	/* Time to gracefully shut down:
 	 * Kill child processes, tell them to call child_exit, etc...
 	 */
 	if (unixd_killpg(getpgrp(), SIGTERM) < 0) {
 	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "killpg SIGTERM");
