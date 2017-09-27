 static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
 {
     disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
 
     /* This case should not happen... */
     if (!dobj->hfd) {
-        /* XXX log message */
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                 "disk_cache: recalling headers; but no header fd for %s", dobj->name);
         return APR_NOTFOUND;
     }
 
     h->req_hdrs = apr_table_make(r->pool, 20);
     h->resp_hdrs = apr_table_make(r->pool, 20);
 
