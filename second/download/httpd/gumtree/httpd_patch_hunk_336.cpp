 }
 
 static void set_signals(void)
 {
 #ifndef NO_USE_SIGACTION
     struct sigaction sa;
+#endif
 
+    if (!one_process) {
+        ap_fatal_signal_setup(ap_server_conf, pconf);
+    }
+
+#ifndef NO_USE_SIGACTION
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
 
-    if (!one_process) {
-	sa.sa_handler = sig_coredump;
-#if defined(SA_ONESHOT)
-	sa.sa_flags = SA_ONESHOT;
-#elif defined(SA_RESETHAND)
-	sa.sa_flags = SA_RESETHAND;
-#endif
-	if (sigaction(SIGSEGV, &sa, NULL) < 0)
-	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGSEGV)");
-#ifdef SIGBUS
-	if (sigaction(SIGBUS, &sa, NULL) < 0)
-	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGBUS)");
-#endif
-#ifdef SIGABORT
-	if (sigaction(SIGABORT, &sa, NULL) < 0)
-	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGABORT)");
-#endif
-#ifdef SIGABRT
-	if (sigaction(SIGABRT, &sa, NULL) < 0)
-	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGABRT)");
-#endif
-#ifdef SIGILL
-	if (sigaction(SIGILL, &sa, NULL) < 0)
-	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGILL)");
-#endif
-	sa.sa_flags = 0;
-    }
     sa.sa_handler = sig_term;
     if (sigaction(SIGTERM, &sa, NULL) < 0)
 	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGTERM)");
 #ifdef SIGINT
     if (sigaction(SIGINT, &sa, NULL) < 0)
         ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGINT)");
