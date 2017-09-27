                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "attempt to make remote request from mod_rewrite "
                               "without proxy enabled: %s", r->filename);
                 return HTTP_FORBIDDEN;
             }
 
+            if (rulestatus == ACTION_NOESCAPE) {
+                apr_table_setn(r->notes, "proxy-nocanon", "1");
+            }
+
             /* make sure the QUERY_STRING and
              * PATH_INFO parts get incorporated
              */
             if (r->path_info != NULL) {
                 r->filename = apr_pstrcat(r->pool, r->filename,
                                           r->path_info, NULL);
