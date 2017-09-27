     locks_hooks = DAV_GET_HOOKS_LOCKS(r);
     if (locks_hooks == NULL)
         return DECLINED;
 
     if ((const_locktoken_txt = apr_table_get(r->headers_in,
                                              "Lock-Token")) == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00596)
                       "Unlock failed (%s):  "
                       "No Lock-Token specified in header", r->filename);
         return HTTP_BAD_REQUEST;
     }
 
     locktoken_txt = apr_pstrdup(r->pool, const_locktoken_txt);
