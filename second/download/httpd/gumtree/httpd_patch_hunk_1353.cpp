 }
 
 AP_DECLARE(void) ap_send_interim_response(request_rec *r, int send_headers)
 {
     hdr_ptr x;
     char *status_line = NULL;
+    request_rec *rr;
 
     if (r->proto_num < 1001) {
         /* don't send interim response to HTTP/1.0 Client */
         return;
     }
     if (!ap_is_HTTP_INFO(r->status)) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                       "Status is %d - not sending interim response", r->status);
         return;
     }
 
+    /* if we send an interim response, we're no longer in a state of
+     * expecting one.  Also, this could feasibly be in a subrequest,
+     * so we need to propagate the fact that we responded.
+     */
+    for (rr = r; rr != NULL; rr = rr->main) {
+        rr->expecting_100 = 0;
+    }
+
     status_line = apr_pstrcat(r->pool, AP_SERVER_PROTOCOL, " ", r->status_line, CRLF, NULL);
     ap_xlate_proto_to_ascii(status_line, strlen(status_line));
 
     x.f = r->connection->output_filters;
     x.bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
 
