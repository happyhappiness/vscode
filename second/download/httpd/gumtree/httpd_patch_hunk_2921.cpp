     }
 
     /* perform sub-request for the file name without the suffix */
     result = 0;
     sub_filename = apr_pstrndup(r->pool, r->filename, suffix_pos);
 #if MIME_MAGIC_DEBUG
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01556)
                 MODNAME ": subrequest lookup for %s", sub_filename);
 #endif /* MIME_MAGIC_DEBUG */
     sub = ap_sub_req_lookup_file(sub_filename, r, NULL);
 
     /* extract content type/encoding/language from sub-request */
     if (sub->content_type) {
         ap_set_content_type(r, apr_pstrdup(r->pool, sub->content_type));
 #if MIME_MAGIC_DEBUG
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01557)
                     MODNAME ": subrequest %s got %s",
                     sub_filename, r->content_type);
 #endif /* MIME_MAGIC_DEBUG */
         if (sub->content_encoding)
             r->content_encoding =
                 apr_pstrdup(r->pool, sub->content_encoding);
