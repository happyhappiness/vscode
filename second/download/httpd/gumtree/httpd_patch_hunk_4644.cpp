             return APR_EGENERAL;
     }
     return status;
 }
 
 
+/* Unixes MPMs' */
+
+static ap_unixd_mpm_retained_data *retained_data = NULL;
+AP_DECLARE(ap_unixd_mpm_retained_data *) ap_unixd_mpm_get_retained_data()
+{
+    if (!retained_data) {
+        retained_data = ap_retained_data_create("ap_unixd_mpm_retained_data",
+                                                sizeof(*retained_data));
+        retained_data->mpm_state = AP_MPMQ_STARTING;
+    }
+    return retained_data;
+}
+
+static void sig_term(int sig)
+{
+    retained_data->mpm_state = AP_MPMQ_STOPPING;
+    if (retained_data->shutdown_pending
+            && (retained_data->is_ungraceful
+                || sig == AP_SIG_GRACEFUL_STOP)) {
+        /* Already handled */
+        return;
+    }
+
+    retained_data->shutdown_pending = 1;
+    if (sig != AP_SIG_GRACEFUL_STOP) {
+        retained_data->is_ungraceful = 1;
+    }
+}
+
+static void sig_restart(int sig)
+{
+    retained_data->mpm_state = AP_MPMQ_STOPPING;
+    if (retained_data->restart_pending
+            && (retained_data->is_ungraceful
+                || sig == AP_SIG_GRACEFUL)) {
+        /* Already handled */
+        return;
+    }
+
+    retained_data->restart_pending = 1;
+    if (sig != AP_SIG_GRACEFUL) {
+        retained_data->is_ungraceful = 1;
+    }
+}
+
+static apr_status_t unset_signals(void *unused)
+{
+    retained_data->shutdown_pending = retained_data->restart_pending = 0;
+    retained_data->was_graceful = !retained_data->is_ungraceful;
+    retained_data->is_ungraceful = 0;
+
+    return APR_SUCCESS;
+}
+
+AP_DECLARE(void) ap_unixd_mpm_set_signals(apr_pool_t *pconf, int one_process)
+{
+#ifndef NO_USE_SIGACTION
+    struct sigaction sa;
+#endif
+
+    /* Signals' handlers depend on retained data */
+    (void)ap_unixd_mpm_get_retained_data();
+
+#ifndef NO_USE_SIGACTION
+    memset(&sa, 0, sizeof sa);
+    sigemptyset(&sa.sa_mask);
+
+#ifdef SIGPIPE
+    sa.sa_handler = SIG_IGN;
+    if (sigaction(SIGPIPE, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00269)
+                     "sigaction(SIGPIPE)");
+#endif
+#ifdef SIGXCPU
+    sa.sa_handler = SIG_DFL;
+    if (sigaction(SIGXCPU, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00267)
+                     "sigaction(SIGXCPU)");
+#endif
+#ifdef SIGXFSZ
+    /* For systems following the LFS standard, ignoring SIGXFSZ allows
+     * a write() beyond the 2GB limit to fail gracefully with E2BIG
+     * rather than terminate the process. */
+    sa.sa_handler = SIG_IGN;
+    if (sigaction(SIGXFSZ, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00268)
+                     "sigaction(SIGXFSZ)");
+#endif
+
+    sa.sa_handler = sig_term;
+    if (sigaction(SIGTERM, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00264)
+                     "sigaction(SIGTERM)");
+#ifdef SIGINT
+    if (sigaction(SIGINT, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00266)
+                     "sigaction(SIGINT)");
+#endif
+#ifdef AP_SIG_GRACEFUL_STOP
+    if (sigaction(AP_SIG_GRACEFUL_STOP, &sa, NULL) < 0)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00265)
+                     "sigaction(" AP_SIG_GRACEFUL_STOP_STRING ")");
+#endif
+
+    /* Don't catch restart signals in ONE_PROCESS mode :) */
+    if (!one_process) {
+        sa.sa_handler = sig_restart;
+        if (sigaction(SIGHUP, &sa, NULL) < 0)
+            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00270)
+                         "sigaction(SIGHUP)");
+        if (sigaction(AP_SIG_GRACEFUL, &sa, NULL) < 0)
+            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00271)
+                         "sigaction(" AP_SIG_GRACEFUL_STRING ")");
+    }
+
+#else  /* NO_USE_SIGACTION */
+
+#ifdef SIGPIPE
+    apr_signal(SIGPIPE, SIG_IGN);
+#endif /* SIGPIPE */
+#ifdef SIGXCPU
+    apr_signal(SIGXCPU, SIG_DFL);
+#endif /* SIGXCPU */
+#ifdef SIGXFSZ
+    apr_signal(SIGXFSZ, SIG_IGN);
+#endif /* SIGXFSZ */
+
+    apr_signal(SIGTERM, sig_term);
+#ifdef AP_SIG_GRACEFUL_STOP
+    apr_signal(AP_SIG_GRACEFUL_STOP, sig_term);
+#endif /* AP_SIG_GRACEFUL_STOP */
+
+    if (!one_process) {
+        /* Don't restart in ONE_PROCESS mode :) */
+#ifdef SIGHUP
+        apr_signal(SIGHUP, sig_restart);
+#endif /* SIGHUP */
+#ifdef AP_SIG_GRACEFUL
+        apr_signal(AP_SIG_GRACEFUL, sig_restart);
+#endif /* AP_SIG_GRACEFUL */
+    }
+
+#endif /* NO_USE_SIGACTION */
+
+    apr_pool_cleanup_register(pconf, NULL, unset_signals,
+                              apr_pool_cleanup_null);
+}
+
+
 #ifdef _OSD_POSIX
 
 #include "apr_lib.h"
 
 #define USER_LEN 8
 
