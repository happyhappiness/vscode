         case AP_MPM_PODX_NORESTART:
             break;
     }
 
     rv = apr_file_write(pod->pod_out, &char_of_death, &one);
     if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(2404)
+        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf, APLOGNO(02404)
                      "write pipe_of_death");
     }
     return rv;
 }
 
 AP_DECLARE(apr_status_t) ap_mpm_podx_signal(ap_pod_t * pod,
