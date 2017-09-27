     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
 
     sa.sa_handler = sig_term;
     if (sigaction(SIGTERM, &sa, NULL) < 0)
 	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGTERM)");
+#ifdef AP_SIG_GRACEFUL_STOP
+    if (sigaction(AP_SIG_GRACEFUL_STOP, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
+                     "sigaction(" AP_SIG_GRACEFUL_STOP_STRING ")");
+#endif
 #ifdef SIGINT
     if (sigaction(SIGINT, &sa, NULL) < 0)
         ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGINT)");
 #endif
 #ifdef SIGXCPU
     sa.sa_handler = SIG_DFL;
