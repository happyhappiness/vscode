 
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
     sa.sa_handler = sig_term;
 
     if (sigaction(SIGTERM, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGTERM)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00198) "sigaction(SIGTERM)");
 
     sa.sa_handler = sig_hup;
 
     if (sigaction(SIGHUP, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGHUP)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00199) "sigaction(SIGHUP)");
 }
