     ap_reopen_scoreboard(pchild, NULL, 0);
 
     rv = SAFE_ACCEPT(apr_proc_mutex_child_init(&accept_mutex,
                                                apr_proc_mutex_lockfile(accept_mutex),
                                                pchild));
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf, APLOGNO(00280)
                      "Couldn't initialize cross-process lock in child");
         clean_child_exit(APEXIT_CHILDFATAL);
     }
 
     if (ap_run_drop_privileges(pchild, ap_server_conf)) {
         clean_child_exit(APEXIT_CHILDFATAL);
