 #else
     sa.sa_flags = 0;
 #endif
 
     sa.sa_handler = sig_coredump;
     if (sigaction(SIGSEGV, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGSEGV)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00061) "sigaction(SIGSEGV)");
 #ifdef SIGBUS
     if (sigaction(SIGBUS, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGBUS)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00062) "sigaction(SIGBUS)");
 #endif
 #ifdef SIGABORT
     if (sigaction(SIGABORT, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABORT)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00063) "sigaction(SIGABORT)");
 #endif
 #ifdef SIGABRT
     if (sigaction(SIGABRT, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABRT)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00064) "sigaction(SIGABRT)");
 #endif
 #ifdef SIGILL
     if (sigaction(SIGILL, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGILL)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00065) "sigaction(SIGILL)");
 #endif
 #ifdef SIGFPE
     if (sigaction(SIGFPE, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGFPE)");
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00066) "sigaction(SIGFPE)");
 #endif
 
 #else /* NO_USE_SIGACTION */
 
     apr_signal(SIGSEGV, sig_coredump);
 #ifdef SIGBUS
