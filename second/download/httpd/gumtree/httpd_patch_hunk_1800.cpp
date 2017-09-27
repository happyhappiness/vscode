              */
             ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                          "apr_socket_accept: giving up.");
             return APR_EGENERAL;
 #endif /*ENETDOWN*/
 
-#ifdef TPF
-        case EINACT:
-            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
-                         "offload device inactive");
-            return APR_EGENERAL;
-            break;
-        default:
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
-                         "select/accept error (%d)", status);
-            return APR_EGENERAL;
-#else
         default:
+            /* If the socket has been closed in ap_close_listeners()
+             * by the restart/stop action, we may get EBADF.
+             * Do not print an error in this case.
+             */
+            if (!lr->active) {
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, status, ap_server_conf,
+                             "apr_socket_accept failed for inactive listener");
+                return status;
+            }
             ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
                          "apr_socket_accept: (client socket)");
             return APR_EGENERAL;
-#endif
     }
     return status;
 }
 
 
 #ifdef _OSD_POSIX
