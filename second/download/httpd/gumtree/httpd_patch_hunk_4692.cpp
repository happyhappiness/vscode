 AP_DECLARE(apr_status_t) ap_fatal_signal_setup(server_rec *s,
                                                apr_pool_t *in_pconf)
 {
 #ifndef NO_USE_SIGACTION
     struct sigaction sa;
 
+    memset(&sa, 0, sizeof sa);
     sigemptyset(&sa.sa_mask);
 
 #if defined(SA_ONESHOT)
     sa.sa_flags = SA_ONESHOT;
 #elif defined(SA_RESETHAND)
     sa.sa_flags = SA_RESETHAND;
-#else
-    sa.sa_flags = 0;
 #endif
 
     sa.sa_handler = sig_coredump;
     if (sigaction(SIGSEGV, &sa, NULL) < 0)
         ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, APLOGNO(00061) "sigaction(SIGSEGV)");
 #ifdef SIGBUS
