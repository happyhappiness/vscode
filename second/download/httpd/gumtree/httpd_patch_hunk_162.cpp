 
             rc = ap_os_create_privileged_process(r, procnew, argv0, argv, 
                                                  (const char * const *)env, 
                                                  procattr, ptrans);
 
             if (rc != APR_SUCCESS) {
-                /* Bad things happened. Everyone should have cleaned up. */
-                ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
-                              "couldn't create child process: %d: %s", rc, 
-                              apr_filename_of_pathname(r->filename));
+                /* Bad things happened. Everyone should have cleaned up.
+                 * ap_log_rerror() won't work because the header table used by
+                 * ap_log_rerror() hasn't been replicated in the phony r
+                 */
+                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
+                             "couldn't create child process: %d: %s", rc, 
+                             apr_filename_of_pathname(r->filename));
             }
             else {
                 apr_hash_set(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id), 
                              (void *)procnew->pid);
             }
         }
