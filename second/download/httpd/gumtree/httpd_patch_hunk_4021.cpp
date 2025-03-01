     }
     else {
         return apr_table_make(pool, 0);        
     }
 }
 
+static const char *get_sos_filter(apr_table_t *notes) 
+{
+    return notes? apr_table_get(notes, H2_RESP_SOS_NOTE) : NULL;
+}
+
+static void check_clen(h2_response *response, request_rec *r, apr_pool_t *pool)
+{
+    
+    if (r && r->header_only) {
+        response->content_length = 0;
+    }
+    else if (response->headers) {
+        const char *s = apr_table_get(response->headers, "Content-Length");
+        if (s) {
+            char *end;
+            response->content_length = apr_strtoi64(s, &end, 10);
+            if (s == end) {
+                ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, 
+                              pool, APLOGNO(02956) 
+                              "h2_response: content-length"
+                              " value not parsed: %s", s);
+                response->content_length = -1;
+            }
+        }
+    }
+}
+
 static h2_response *h2_response_create_int(int stream_id,
                                            int rst_error,
                                            int http_status,
                                            apr_table_t *headers,
+                                           apr_table_t *notes,
                                            apr_pool_t *pool)
 {
     h2_response *response;
-    const char *s;
 
     if (!headers) {
         return NULL;
     }
     
     response = apr_pcalloc(pool, sizeof(h2_response));
     if (response == NULL) {
         return NULL;
     }
     
-    response->stream_id = stream_id;
-    response->rst_error = rst_error;
-    response->http_status = http_status? http_status : 500;
+    response->stream_id      = stream_id;
+    response->rst_error      = rst_error;
+    response->http_status    = http_status? http_status : 500;
     response->content_length = -1;
-    response->headers = headers;
+    response->headers        = headers;
+    response->sos_filter     = get_sos_filter(notes);
     
-    s = apr_table_get(headers, "Content-Length");
-    if (s) {
-        char *end;
-        
-        response->content_length = apr_strtoi64(s, &end, 10);
-        if (s == end) {
-            ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, 
-                          pool, APLOGNO(02956) 
-                          "h2_response: content-length"
-                          " value not parsed: %s", s);
-            response->content_length = -1;
-        }
-    }
+    check_clen(response, NULL, pool);
     return response;
 }
 
 
 h2_response *h2_response_create(int stream_id,
                                 int rst_error,
                                 int http_status,
                                 apr_array_header_t *hlines,
+                                apr_table_t *notes,
                                 apr_pool_t *pool)
 {
     return h2_response_create_int(stream_id, rst_error, http_status,
-                                  parse_headers(hlines, pool), pool);
+                                  parse_headers(hlines, pool), notes, pool);
 }
 
 h2_response *h2_response_rcreate(int stream_id, request_rec *r,
                                  apr_table_t *header, apr_pool_t *pool)
 {
     h2_response *response = apr_pcalloc(pool, sizeof(h2_response));
     if (response == NULL) {
         return NULL;
     }
     
-    response->stream_id = stream_id;
-    response->http_status = r->status;
+    response->stream_id      = stream_id;
+    response->http_status    = r->status;
     response->content_length = -1;
-    response->headers = header;
+    response->headers        = header;
+    response->sos_filter     = get_sos_filter(r->notes);
 
+    check_clen(response, r, pool);
+    
     if (response->http_status == HTTP_FORBIDDEN) {
         const char *cause = apr_table_get(r->notes, "ssl-renegotiate-forbidden");
         if (cause) {
             /* This request triggered a TLS renegotiation that is now allowed 
              * in HTTP/2. Tell the client that it should use HTTP/1.1 for this.
              */
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, response->http_status, r, 
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, response->http_status, r,
+                          APLOGNO(03061) 
                           "h2_response(%ld-%d): renegotiate forbidden, cause: %s",
                           (long)r->connection->id, stream_id, cause);
             response->rst_error = H2_ERR_HTTP_1_1_REQUIRED;
         }
     }
     
