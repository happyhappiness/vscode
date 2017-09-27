         return APR_SUCCESS;
     }
     return get_remaining_chunk_line(ctx, b, linelimit);
 }
 
 
+static apr_status_t read_chunked_trailers(http_ctx_t *ctx, ap_filter_t *f,
+                                          apr_bucket_brigade *b, int merge)
+{
+    int rv;
+    apr_bucket *e;
+    request_rec *r = f->r;
+    apr_table_t *saved_headers_in = r->headers_in;
+    int saved_status = r->status;
+
+    r->status = HTTP_OK;
+    r->headers_in = r->trailers_in;
+    apr_table_clear(r->headers_in);
+    ctx->state = BODY_NONE;
+    ap_get_mime_headers(r);
+
+    if(r->status == HTTP_OK) {
+        r->status = saved_status;
+        e = apr_bucket_eos_create(f->c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(b, e);
+        ctx->eos_sent = 1;
+        rv = APR_SUCCESS;
+    }
+    else {
+        const char *error_notes = apr_table_get(r->notes,
+                                                "error-notes");
+        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, 
+                      "Error while reading HTTP trailer: %i%s%s",
+                      r->status, error_notes ? ": " : "",
+                      error_notes ? error_notes : "");
+        rv = APR_EINVAL;
+    }
+
+    if(!merge) {
+        r->headers_in = saved_headers_in;
+    }
+    else {
+        r->headers_in = apr_table_overlay(r->pool, saved_headers_in,
+                r->trailers_in);
+    }
+
+    return rv;
+}
+
 /* This is the HTTP_INPUT filter for HTTP requests and responses from
  * proxied servers (mod_proxy).  It handles chunked and content-length
  * bodies.  This can only be inserted/used after the headers
  * are successfully parsed.
  */
 apr_status_t ap_http_filter(ap_filter_t *f, apr_bucket_brigade *b,
                             ap_input_mode_t mode, apr_read_type_e block,
                             apr_off_t readbytes)
 {
+    core_server_config *conf;
     apr_bucket *e;
     http_ctx_t *ctx = f->ctx;
     apr_status_t rv;
     apr_off_t totalread;
     int http_error = HTTP_REQUEST_ENTITY_TOO_LARGE;
     apr_bucket_brigade *bb;
 
+    conf = (core_server_config *)
+        ap_get_module_config(f->r->server->module_config, &core_module);
+
     /* just get out of the way of things we don't want. */
     if (mode != AP_MODE_READBYTES && mode != AP_MODE_GETLINE) {
         return ap_get_brigade(f->next, b, mode, block, readbytes);
     }
 
     if (!ctx) {
