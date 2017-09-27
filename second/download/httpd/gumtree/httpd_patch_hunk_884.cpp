  * assume means something serious is wrong (which it will be, for the
  * child to force an exit) and so do an exit anyway.
  */
 
 static void ap_start_shutdown(void)
 {
-    mpm_state = AP_MPMQ_STOPPING;
- 
-    if (shutdown_pending == 1) {
-	/* Um, is this _probably_ not an error, if the user has
-	 * tried to do a shutdown twice quickly, so we won't
-	 * worry about reporting it.
-	 */
+    /* If the user tries to shut us down twice in quick succession then we
+     * may well get triggered while we are working through previous attempt
+     * to shutdown. We won't worry about even reporting it as it seems a little
+     * pointless.
+     */
+    if (shutdown_pending == 1)
 	return;
-    }
+
     shutdown_pending = 1;
 }
 
 /* do a graceful restart if graceful == 1 */
 static void ap_start_restart(int graceful)
 {
-    mpm_state = AP_MPMQ_STOPPING;
-
     if (restart_pending == 1) {
         /* Probably not an error - don't bother reporting it */
         return;
     }
     restart_pending = 1;
     is_graceful = graceful;
 }
 
+/* sig_coredump attempts to handle all the potential signals we
+ * may get that should result in a core dump. This is called from
+ * the signal handler routine, so when we enter we are essentially blocked
+ * on the signal. Once we exit we will allow the signal to be processed by
+ * system, which may or may not produce a .core file. All this function does
+ * is try and respect the users wishes about where that file should be
+ * located (chdir) and then signal the parent with the signal.
+ *
+ * If we called abort() the parent would only see SIGABRT which doesn't provide
+ * as much information.
+ */
+static void sig_coredump(int sig)
+{
+    chdir(ap_coredump_dir);
+    signal(sig, SIG_DFL);
+    kill(server_pid, sig);
+}
+
 static void sig_term(int sig)
 {
     ap_start_shutdown();
 }
 
 static void restart(int sig)
 {
     ap_start_restart(sig == AP_SIG_GRACEFUL);
 }
 
+/* Handle queries about our inner workings... */
+AP_DECLARE(apr_status_t) ap_mpm_query(int query_code, int *result)
+{
+    switch(query_code){
+        case AP_MPMQ_MAX_DAEMON_USED:
+            *result = ap_max_child_assigned;
+            return APR_SUCCESS;
+        case AP_MPMQ_IS_THREADED:
+            *result = AP_MPMQ_DYNAMIC;
+            return APR_SUCCESS;
+        case AP_MPMQ_IS_FORKED:
+            *result = AP_MPMQ_NOT_SUPPORTED;
+            return APR_SUCCESS;
+        case AP_MPMQ_HARD_LIMIT_DAEMONS:
+            *result = HARD_SERVER_LIMIT;
+            return APR_SUCCESS;
+        case AP_MPMQ_HARD_LIMIT_THREADS:
+            *result = HARD_THREAD_LIMIT;
+            return APR_SUCCESS;
+        case AP_MPMQ_MAX_THREADS:
+            *result = HARD_THREAD_LIMIT;
+            return APR_SUCCESS;
+        case AP_MPMQ_MIN_SPARE_DAEMONS:
+            *result = 0;
+            return APR_SUCCESS;
+        case AP_MPMQ_MIN_SPARE_THREADS:
+            *result = max_spare_threads;
+            return APR_SUCCESS;
+        case AP_MPMQ_MAX_SPARE_DAEMONS:
+            *result = 0;
+            return APR_SUCCESS;
+        case AP_MPMQ_MAX_SPARE_THREADS:
+            *result = min_spare_threads;
+            return APR_SUCCESS;
+        case AP_MPMQ_MAX_REQUESTS_DAEMON:
+            *result = ap_max_requests_per_thread;
+            return APR_SUCCESS;
+        case AP_MPMQ_MAX_DAEMONS:
+            *result = HARD_SERVER_LIMIT;
+            return APR_SUCCESS;
+        case AP_MPMQ_MPM_STATE:
+            *result = mpm_state;
+            return APR_SUCCESS;
+    }
+    return APR_ENOTIMPL;
+}
+
+/* This accepts a connection and allows us to handle the error codes better than
+ * the previous code, while also making it more obvious.
+ */
+static apr_status_t beos_accept(void **accepted, ap_listen_rec *lr, apr_pool_t *ptrans)
+{
+    apr_socket_t *csd;
+    apr_status_t status;
+    int sockdes;
+
+    *accepted = NULL;
+    status = apr_socket_accept(&csd, lr->sd, ptrans);
+    if (status == APR_SUCCESS) {
+        *accepted = csd;
+        apr_os_sock_get(&sockdes, csd);
+        return status;
+    }
+
+    if (APR_STATUS_IS_EINTR(status)) {
+        return status;
+    }
+        /* This switch statement provides us with better error details. */
+    switch (status) {
+#ifdef ECONNABORTED
+        case ECONNABORTED:
+#endif
+#ifdef ETIMEDOUT
+        case ETIMEDOUT:
+#endif
+#ifdef EHOSTUNREACH
+        case EHOSTUNREACH:
+#endif
+#ifdef ENETUNREACH
+        case ENETUNREACH:
+#endif
+            break;
+#ifdef ENETDOWN
+        case ENETDOWN:
+            /*
+             * When the network layer has been shut down, there
+             * is not much use in simply exiting: the parent
+             * would simply re-create us (and we'd fail again).
+             * Use the CHILDFATAL code to tear the server down.
+             * @@@ Martin's idea for possible improvement:
+             * A different approach would be to define
+             * a new APEXIT_NETDOWN exit code, the reception
+             * of which would make the parent shutdown all
+             * children, then idle-loop until it detected that
+             * the network is up again, and restart the children.
+             * Ben Hyde noted that temporary ENETDOWN situations
+             * occur in mobile IP.
+             */
+            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
+                         "apr_socket_accept: giving up.");
+            return APR_EGENERAL;
+#endif /*ENETDOWN*/
+
+        default:
+            ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
+                         "apr_socket_accept: (client socket)");
+            return APR_EGENERAL;
+    }
+    return status;
+}
+
 static void tell_workers_to_exit(void)
 {
     apr_size_t len;
     int i = 0;
-
-    mpm_state = AP_MPMQ_STOPPING;
-
     for (i = 0 ; i < ap_max_child_assigned; i++){
         len = 4;
-        if (apr_sendto(udp_sock, udp_sa, 0, "die!", &len) != APR_SUCCESS)
+        if (apr_socket_sendto(udp_sock, udp_sa, 0, "die!", &len) != APR_SUCCESS)
             break;
-    }   
+    }
 }
 
 static void set_signals(void)
 {
     struct sigaction sa;
 
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;
 
+    /* The first batch get handled by sig_coredump */
     if (!one_process) {
 	sa.sa_handler = sig_coredump;
 
 	if (sigaction(SIGSEGV, &sa, NULL) < 0)
 	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGSEGV)");
 	if (sigaction(SIGBUS, &sa, NULL) < 0)
