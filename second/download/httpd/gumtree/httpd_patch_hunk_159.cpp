                                       conf->limit_nproc)) != APR_SUCCESS) ||
 #endif
         ((rc = apr_procattr_cmdtype_set(procattr,
                                         e_info->cmd_type)) != APR_SUCCESS) ||
 
         ((rc = apr_procattr_detach_set(procattr,
-                                        e_info->detached)) != APR_SUCCESS)) {
+                                        e_info->detached)) != APR_SUCCESS) ||
+        ((rc = apr_procattr_child_errfn_set(procattr, cgi_child_errfn)) != APR_SUCCESS)) {
         /* Something bad happened, tell the world. */
         ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                       "couldn't set child process attributes: %s", r->filename);
     }
     else {
+        apr_pool_userdata_set(r, ERRFN_USERDATA_KEY, apr_pool_cleanup_null, p);
+
         procnew = apr_pcalloc(p, sizeof(*procnew));
         if (e_info->prog_type == RUN_AS_SSI) {
             SPLIT_AND_PASS_PRETAG_BUCKETS(*(e_info->bb), e_info->ctx,
                                           e_info->next, rc);
             if (rc != APR_SUCCESS) {
                 return rc;
