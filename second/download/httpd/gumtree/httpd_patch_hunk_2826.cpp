     }
 
     for (i = 0; i < format->nelts; ++i) {
         len += strl[i] = strlen(strs[i]);
     }
     if (!log_writer) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00645)
                 "log writer isn't correctly setup");
          return HTTP_INTERNAL_SERVER_ERROR;
     }
     rv = log_writer(r, cls->log_writer, strs, strl, format->nelts, len);
-    /* xxx: do we return an error on log_writer? */
+    if (rv != APR_SUCCESS)
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(00646) "Error writing to %s",
+                      cls->fname);
     return OK;
 }
 
 static int multi_log_transaction(request_rec *r)
 {
     multi_log_state *mls = ap_get_module_config(r->server->module_config,
