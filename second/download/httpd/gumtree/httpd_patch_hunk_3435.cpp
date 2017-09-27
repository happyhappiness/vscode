     apr_status_t rv;
     char char_of_death = graceful ? GRACEFUL_CHAR : RESTART_CHAR;
     apr_size_t one = 1;
 
     rv = apr_file_write(pod->pod_out, &char_of_death, &one);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(00325)
                      "write pipe_of_death");
     }
     return rv;
 }
 
 AP_DECLARE(apr_status_t) ap_worker_pod_signal(ap_worker_pod_t *pod, int graceful)
