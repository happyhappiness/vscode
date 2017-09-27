      * came in over the network.
      */
     apr_file_printf(stderr_log,
                     "(%d)%s: %s\n",
                     err,
                     apr_strerror(err, errbuf, sizeof(errbuf)),
-#ifdef AP_UNSAFE_ERROR_LOG_UNESCAPED
+#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
+                    ap_escape_logitem(pool,
+#endif
                     description
-#else
-                    ap_escape_logitem(pool, description)
+#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
+                    )
 #endif
                     );
 }
 
 static apr_status_t run_cgi_child(apr_file_t **script_out,
                                   apr_file_t **script_in,
-                                  apr_file_t **script_err, 
+                                  apr_file_t **script_err,
                                   const char *command,
                                   const char * const argv[],
                                   request_rec *r,
                                   apr_pool_t *p,
                                   cgi_exec_info_t *e_info)
 {
