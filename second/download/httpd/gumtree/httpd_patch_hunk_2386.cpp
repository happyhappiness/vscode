         else {
             ret = HTTP_FORBIDDEN;
         }
     }
 
     if (ret == HTTP_FORBIDDEN) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01797)
                       "client denied by server configuration: %s%s",
                       r->filename ? "" : "uri ",
                       r->filename ? r->filename : r->uri);
     }
 
     return ret;
