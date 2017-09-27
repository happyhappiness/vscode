 
         apr_rfc822_date(datestr, mod_time);
         apr_table_setn(r->headers_out, "Last-Modified", datestr);
     }
 }
 
+typedef struct hdr_ptr {
+    ap_filter_t *f;
+    apr_bucket_brigade *bb;
+} hdr_ptr;
+
+static int send_header(void *data, const char *key, const char *val)
+{
+    ap_fputstrs(((hdr_ptr*)data)->f, ((hdr_ptr*)data)->bb,
+                key, ": ", val, CRLF, NULL);
+    return 1;
+}
+
+AP_DECLARE(void) ap_send_interim_response(request_rec *r, int send_headers)
+{
+    hdr_ptr x;
+
+    if (r->proto_num < 1001) {
+        /* don't send interim response to HTTP/1.0 Client */
+        return;
+    }
+    if (!ap_is_HTTP_INFO(r->status)) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, NULL,
+                      "Status is %d - not sending interim response", r->status);
+        return;
+    }
+
+    x.f = r->connection->output_filters;
+    x.bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
+    ap_fputstrs(x.f, x.bb, AP_SERVER_PROTOCOL, " ", r->status_line, CRLF, NULL);
+    if (send_headers) {
+        apr_table_do(send_header, &x, r->headers_out, NULL);
+        apr_table_clear(r->headers_out);
+    }
+    ap_fputs(x.f, x.bb, CRLF);
+    ap_fflush(x.f, x.bb);
+    apr_brigade_destroy(x.bb);
+}
+
 AP_IMPLEMENT_HOOK_RUN_ALL(int,post_read_request,
                           (request_rec *r), (r), OK, DECLINED)
 AP_IMPLEMENT_HOOK_RUN_ALL(int,log_transaction,
                           (request_rec *r), (r), OK, DECLINED)
 AP_IMPLEMENT_HOOK_RUN_FIRST(const char *,http_scheme,
                             (const request_rec *r), (r), NULL)
