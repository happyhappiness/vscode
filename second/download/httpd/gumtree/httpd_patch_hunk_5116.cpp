                      "write pipe_of_death");
     }
 
     return rv;
 }
 
+AP_DECLARE(apr_status_t) ap_mpm_podx_open(apr_pool_t *p, ap_pod_t **pod)
+{
+    apr_status_t rv;
+
+    *pod = apr_palloc(p, sizeof(**pod));
+    rv = apr_file_pipe_create(&((*pod)->pod_in), &((*pod)->pod_out), p);
+    if (rv != APR_SUCCESS) {
+        return rv;
+    }
+    /*
+     apr_file_pipe_timeout_set((*pod)->pod_in, 0);
+     */
+    (*pod)->p = p;
+
+    /* close these before exec. */
+    apr_file_inherit_unset((*pod)->pod_in);
+    apr_file_inherit_unset((*pod)->pod_out);
+
+    return APR_SUCCESS;
+}
+
+AP_DECLARE(int) ap_mpm_podx_check(ap_pod_t *pod)
+{
+    char c;
+    apr_os_file_t fd;
+    int rc;
+
+    /* we need to surface EINTR so we'll have to grab the
+     * native file descriptor and do the OS read() ourselves
+     */
+    apr_os_file_get(&fd, pod->pod_in);
+    rc = read(fd, &c, 1);
+    if (rc == 1) {
+        switch (c) {
+            case AP_MPM_PODX_RESTART_CHAR:
+                return AP_MPM_PODX_RESTART;
+            case AP_MPM_PODX_GRACEFUL_CHAR:
+                return AP_MPM_PODX_GRACEFUL;
+        }
+    }
+    return AP_MPM_PODX_NORESTART;
+}
+
+AP_DECLARE(apr_status_t) ap_mpm_podx_close(ap_pod_t *pod)
+{
+    apr_status_t rv;
+
+    rv = apr_file_close(pod->pod_out);
+    if (rv != APR_SUCCESS) {
+        return rv;
+    }
+
+    rv = apr_file_close(pod->pod_in);
+    if (rv != APR_SUCCESS) {
+        return rv;
+    }
+    return rv;
+}
+
+static apr_status_t podx_signal_internal(ap_pod_t *pod,
+                                        ap_podx_restart_t graceful)
+{
+    apr_status_t rv;
+    apr_size_t one = 1;
+    char char_of_death = ' ';
+    switch (graceful) {
+        case AP_MPM_PODX_RESTART:
+            char_of_death = AP_MPM_PODX_RESTART_CHAR;
+            break;
+        case AP_MPM_PODX_GRACEFUL:
+            char_of_death = AP_MPM_PODX_GRACEFUL_CHAR;
+            break;
+        case AP_MPM_PODX_NORESTART:
+            break;
+    }
+
+    rv = apr_file_write(pod->pod_out, &char_of_death, &one);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(2404)
+                     "write pipe_of_death");
+    }
+    return rv;
+}
+
+AP_DECLARE(apr_status_t) ap_mpm_podx_signal(ap_pod_t * pod,
+                                            ap_podx_restart_t graceful)
+{
+    return podx_signal_internal(pod, graceful);
+}
+
+AP_DECLARE(void) ap_mpm_podx_killpg(ap_pod_t * pod, int num,
+                                    ap_podx_restart_t graceful)
+{
+    int i;
+    apr_status_t rv = APR_SUCCESS;
+
+    for (i = 0; i < num && rv == APR_SUCCESS; i++) {
+        rv = podx_signal_internal(pod, graceful);
+    }
+}
+
 /* This function connects to the server and sends enough data to
  * ensure the child wakes up and processes a new connection.  This
  * permits the MPM to skip the poll when there is only one listening
  * socket, because it provides a alternate way to unblock an accept()
  * when the pod is used.  */
 static apr_status_t dummy_connection(ap_pod_t *pod)
