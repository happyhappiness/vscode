     /* This case should not happen... */
     if (!dobj->hfd) {
         /* XXX log message */
         return APR_NOTFOUND;
     }
 
-    if(!r->headers_out) {
-        r->headers_out = apr_table_make(r->pool, 20);
-    }
-
-    /*
-     * Call routine to read the header lines/status line
-     */
-    r->status = dobj->disk_info.status;
-    ap_scan_script_header_err(r, dobj->hfd, NULL);
-
-    apr_table_setn(r->headers_out, "Content-Type",
-                   ap_make_content_type(r, r->content_type));
-
     h->req_hdrs = apr_table_make(r->pool, 20);
+    h->resp_hdrs = apr_table_make(r->pool, 20);
+    h->resp_err_hdrs = apr_table_make(r->pool, 20);
 
-    /*
-     * Call routine to read the header lines/status line
-     *
-     * Note that ap_scan_script_header_err sets to r->err_headers_out,
-     * so we must set the real one aside.
-     */
-    tmp = r->err_headers_out;
-    r->err_headers_out = h->req_hdrs;
-    ap_scan_script_header_err(r, dobj->hfd, NULL);
-    r->err_headers_out = tmp;
+    /* Call routine to read the header lines/status line */
+    read_table(h, r, h->resp_hdrs, dobj->hfd);
+    read_table(h, r, h->req_hdrs, dobj->hfd);
 
     apr_file_close(dobj->hfd);
 
+    h->status = dobj->disk_info.status;
+    h->content_type = apr_table_get(h->resp_hdrs, "Content-Type");
+
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                  "disk_cache: Recalled headers for URL %s",  dobj->name);
     return APR_SUCCESS;
 }
 
 static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb)
