         strs[i] = process_item(r, orig, &items[i]);
     }
 
     for (i = 0; i < format->nelts; ++i) {
         len += strl[i] = strlen(strs[i]);
     }
-
-#ifdef BUFFERED_LOGS
-    if (len + cls->outcnt > LOG_BUFSIZE) {
-        flush_log(cls);
+    if (!log_writer) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, r,
+                "log writer isn't correctly setup");
+         return HTTP_INTERNAL_SERVER_ERROR;
     }
-    if (len >= LOG_BUFSIZE) {
-        apr_size_t w;
-
-        str = apr_palloc(r->pool, len + 1);
-        for (i = 0, s = str; i < format->nelts; ++i) {
-            memcpy(s, strs[i], strl[i]);
-            s += strl[i];
-        }
-        w = len;
-        apr_file_write(cls->log_fd, str, &w);
-    }
-    else {
-        for (i = 0, s = &cls->outbuf[cls->outcnt]; i < format->nelts; ++i) {
-            memcpy(s, strs[i], strl[i]);
-            s += strl[i];
-        }
-        cls->outcnt += len;
-    }
-#else
-    str = apr_palloc(r->pool, len + 1);
-
-    for (i = 0, s = str; i < format->nelts; ++i) {
-        memcpy(s, strs[i], strl[i]);
-        s += strl[i];
-    }
-
-    apr_file_write(cls->log_fd, str, &len);
-#endif
-
+    rv = log_writer(r, cls->log_writer, strs, strl, format->nelts, len);
+    /* xxx: do we return an error on log_writer? */
     return OK;
 }
 
 static int multi_log_transaction(request_rec *r)
 {
     multi_log_state *mls = ap_get_module_config(r->server->module_config,
