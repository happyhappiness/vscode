                */
               ((rc = apr_procattr_child_err_set(procattr, r->server->error_log, NULL)) != APR_SUCCESS) ||
               ((rc = apr_procattr_child_in_set(procattr, inout, NULL)) != APR_SUCCESS))) ||
             ((rc = apr_procattr_child_out_set(procattr, inout, NULL)) != APR_SUCCESS) ||
             ((rc = apr_procattr_dir_set(procattr,
                                   ap_make_dirstr_parent(r->pool, r->filename))) != APR_SUCCESS) ||
-            ((rc = apr_procattr_cmdtype_set(procattr, cmd_type)) != APR_SUCCESS)) {
-            /* Something bad happened, tell the world. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
-                      "couldn't set child process attributes: %s", r->filename);
+            ((rc = apr_procattr_cmdtype_set(procattr, cmd_type)) != APR_SUCCESS) ||
+            ((rc = apr_procattr_child_errfn_set(procattr, cgid_child_errfn)) != APR_SUCCESS)) {
+            /* Something bad happened, tell the world.
+             * ap_log_rerror() won't work because the header table used by
+             * ap_log_rerror() hasn't been replicated in the phony r
+             */
+            ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
+                         "couldn't set child process attributes: %s", r->filename);
         }
         else {
+            apr_pool_userdata_set(r, ERRFN_USERDATA_KEY, apr_pool_cleanup_null, ptrans);
+
             argv = (const char * const *)create_argv(r->pool, NULL, NULL, NULL, argv0, r->args);
 
            /* We want to close sd2 for the new CGI process too.
             * If it is left open it'll make ap_pass_brigade() block
             * waiting for EOF if CGI forked something running long.
             * close(sd2) here should be okay, as CGI channel
