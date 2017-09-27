 #ifndef NO_USE_SIGACTION
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
 
     sa.sa_handler = sig_term;
     if (sigaction(SIGTERM, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGTERM)");
+#ifdef AP_SIG_GRACEFUL_STOP
+    if (sigaction(AP_SIG_GRACEFUL_STOP, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
+                     "sigaction(" AP_SIG_GRACEFUL_STOP_STRING ")");
+#endif
 #ifdef SIGINT
     if (sigaction(SIGINT, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGINT)");
 #endif
 #ifdef SIGXCPU
     sa.sa_handler = SIG_DFL;
     if (sigaction(SIGXCPU, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGXCPU)");
 #endif
 #ifdef SIGXFSZ
     sa.sa_handler = SIG_DFL;
     if (sigaction(SIGXFSZ, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGXFSZ)");
 #endif
 #ifdef SIGPIPE
     sa.sa_handler = SIG_IGN;
     if (sigaction(SIGPIPE, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGPIPE)");
 #endif
 
-    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy 
+    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy
      * processing one */
     sigaddset(&sa.sa_mask, SIGHUP);
     sigaddset(&sa.sa_mask, AP_SIG_GRACEFUL);
     sa.sa_handler = restart;
     if (sigaction(SIGHUP, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(SIGHUP)");
     if (sigaction(AP_SIG_GRACEFUL, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                      "sigaction(" AP_SIG_GRACEFUL_STRING ")");
 #else
     if (!one_process) {
 #ifdef SIGXCPU
         apr_signal(SIGXCPU, SIG_DFL);
 #endif /* SIGXCPU */
