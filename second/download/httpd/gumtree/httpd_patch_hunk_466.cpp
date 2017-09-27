             return rc;
         }
     }
     return OK;
 }
 
+static void add_te_chunked(apr_pool_t *p,
+                           apr_bucket_alloc_t *bucket_alloc,
+                           apr_bucket_brigade *header_brigade)
+{
+    apr_bucket *e;
+    char *buf;
+    const char te_hdr[] = "Transfer-Encoding: chunked" CRLF;
+
+    buf = apr_pmemdup(p, te_hdr, sizeof(te_hdr)-1);
+    ap_xlate_proto_to_ascii(buf, sizeof(te_hdr)-1);
+
+    e = apr_bucket_pool_create(buf, sizeof(te_hdr)-1, p, bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+}
+
+static void add_cl(apr_pool_t *p,
+                   apr_bucket_alloc_t *bucket_alloc,
+                   apr_bucket_brigade *header_brigade,
+                   const char *cl_val)
+{
+    apr_bucket *e;
+    char *buf;
+
+    buf = apr_pstrcat(p, "Content-Length: ",
+                      cl_val,
+                      CRLF,
+                      NULL);
+    ap_xlate_proto_to_ascii(buf, strlen(buf));
+    e = apr_bucket_pool_create(buf, strlen(buf), p, bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+}
+
+#define ASCII_CRLF  "\015\012"
+#define ASCII_ZERO  "\060"
+
+static void terminate_headers(apr_bucket_alloc_t *bucket_alloc,
+                              apr_bucket_brigade *header_brigade)
+{
+    apr_bucket *e;
+
+    /* add empty line at the end of the headers */
+    e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+}
+
+static apr_status_t pass_brigade(apr_bucket_alloc_t *bucket_alloc,
+                                 request_rec *r, proxy_http_conn_t *p_conn,
+                                 conn_rec *origin, apr_bucket_brigade *bb,
+                                 int flush)
+{
+    apr_status_t status;
+
+    if (flush) {
+        apr_bucket *e = apr_bucket_flush_create(bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(bb, e);
+    }
+    status = ap_pass_brigade(origin->output_filters, bb);
+    if (status != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                     "proxy: pass request body failed to %pI (%s)",
+                     p_conn->addr, p_conn->name);
+        return status;
+    }
+    apr_brigade_cleanup(bb);
+    return APR_SUCCESS;
+}
+
+static apr_status_t stream_reqbody_chunked(apr_pool_t *p,
+                                           request_rec *r,
+                                           proxy_http_conn_t *p_conn,
+                                           conn_rec *origin,
+                                           apr_bucket_brigade *header_brigade,
+                                           apr_bucket_brigade *input_brigade)
+{
+    int seen_eos = 0;
+    apr_size_t hdr_len;
+    apr_off_t bytes;
+    apr_status_t status;
+    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
+    apr_bucket_brigade *bb;
+    apr_bucket *e;
+
+    add_te_chunked(p, bucket_alloc, header_brigade);
+    terminate_headers(bucket_alloc, header_brigade);
+
+    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
+    {
+        char chunk_hdr[20];  /* must be here due to transient bucket. */
+
+        /* If this brigade contains EOS, either stop or remove it. */
+        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
+            seen_eos = 1;
+
+            /* We can't pass this EOS to the output_filters. */
+            e = APR_BRIGADE_LAST(input_brigade);
+            apr_bucket_delete(e);
+        }
+
+        apr_brigade_length(input_brigade, 1, &bytes);
+
+        hdr_len = apr_snprintf(chunk_hdr, sizeof(chunk_hdr),
+                               "%" APR_UINT64_T_HEX_FMT CRLF, 
+                               (apr_uint64_t)bytes);
+        
+        ap_xlate_proto_to_ascii(chunk_hdr, hdr_len);
+        e = apr_bucket_transient_create(chunk_hdr, hdr_len,
+                                        bucket_alloc);
+        APR_BRIGADE_INSERT_HEAD(input_brigade, e);
+        
+        /*
+         * Append the end-of-chunk CRLF
+         */
+        e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(input_brigade, e);
+        
+        if (header_brigade) {
+            /* we never sent the header brigade, so go ahead and
+             * take care of that now
+             */
+            bb = header_brigade;
+            APR_BRIGADE_CONCAT(bb, input_brigade);
+            header_brigade = NULL;
+        }
+        else {
+            bb = input_brigade;
+        }
+        
+        /* The request is flushed below this loop with chunk EOS header */
+        status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, 0);
+        if (status != APR_SUCCESS) {
+            return status;
+        }
+
+        if (seen_eos) {
+            break;
+        }
+
+        status = ap_get_brigade(r->input_filters, input_brigade,
+                                AP_MODE_READBYTES, APR_BLOCK_READ,
+                                HUGE_STRING_LEN);
+
+        if (status != APR_SUCCESS) {
+            return status;
+        }
+    }
+
+    if (header_brigade) {
+        /* we never sent the header brigade because there was no request body;
+         * send it now
+         */
+        bb = header_brigade;
+    }
+    else {
+        if (!APR_BRIGADE_EMPTY(input_brigade)) {
+            /* input brigade still has an EOS which we can't pass to the output_filters. */
+            e = APR_BRIGADE_LAST(input_brigade);
+            AP_DEBUG_ASSERT(APR_BUCKET_IS_EOS(e));
+            apr_bucket_delete(e);
+        }
+        bb = input_brigade;
+    }
+
+    e = apr_bucket_immortal_create(ASCII_ZERO ASCII_CRLF
+                                   /* <trailers> */
+                                   ASCII_CRLF,
+                                   5, bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(bb, e);
+
+    /* Now we have headers-only, or the chunk EOS mark; flush it */
+    status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1);
+    return status;
+}
+
+static apr_status_t stream_reqbody_cl(apr_pool_t *p,
+                                      request_rec *r,
+                                      proxy_http_conn_t *p_conn,
+                                      conn_rec *origin,
+                                      apr_bucket_brigade *header_brigade,
+                                      apr_bucket_brigade *input_brigade,
+                                      const char *old_cl_val)
+{
+    int seen_eos = 0;
+    apr_status_t status = APR_SUCCESS;
+    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
+    apr_bucket_brigade *bb;
+    apr_bucket *e;
+    apr_off_t cl_val = 0;
+    apr_off_t bytes;
+    apr_off_t bytes_streamed = 0;
+
+    if (old_cl_val) {
+        add_cl(p, bucket_alloc, header_brigade, old_cl_val);
+        cl_val = atol(old_cl_val);
+    }
+    terminate_headers(bucket_alloc, header_brigade);
+
+    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
+    {
+        apr_brigade_length(input_brigade, 1, &bytes);
+        bytes_streamed += bytes;
+
+        /* If this brigade contains EOS, either stop or remove it. */
+        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
+            seen_eos = 1;
+
+            /* We can't pass this EOS to the output_filters. */
+            e = APR_BRIGADE_LAST(input_brigade);
+            apr_bucket_delete(e);
+        }
+
+        /* C-L < bytes streamed?!?
+         * We will error out after the body is completely
+         * consumed, but we can't stream more bytes at the
+         * back end since they would in part be interpreted
+         * as another request!  If nothing is sent, then
+         * just send nothing.
+         *
+         * Prevents HTTP Response Splitting.
+         */
+        if (bytes_streamed > cl_val)
+             continue;
+
+        if (header_brigade) {
+            /* we never sent the header brigade, so go ahead and
+             * take care of that now
+             */
+            bb = header_brigade;
+            APR_BRIGADE_CONCAT(bb, input_brigade);
+            header_brigade = NULL;
+        }
+        else {
+            bb = input_brigade;
+        }
+        
+        /* Once we hit EOS, we are ready to flush. */
+        status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, seen_eos);
+        if (status != APR_SUCCESS) {
+            return status;
+        }
+
+        if (seen_eos) {
+            break;
+        }
+
+        status = ap_get_brigade(r->input_filters, input_brigade,
+                                AP_MODE_READBYTES, APR_BLOCK_READ,
+                                HUGE_STRING_LEN);
+
+        if (status != APR_SUCCESS) {
+            return status;
+        }
+    }
+    
+    if (bytes_streamed != cl_val) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                     "proxy: client %s given Content-Length did not match"
+                     " number of body bytes read", r->connection->remote_ip);
+        return APR_EOF;
+    }
+
+    if (header_brigade) {
+        /* we never sent the header brigade since there was no request
+         * body; send it now with the flush flag
+         */
+        bb = header_brigade;
+        status = pass_brigade(bucket_alloc, r, p_conn, origin, bb, 1);
+    }
+    return status;
+}
+
+#define MAX_MEM_SPOOL 16384
+
+static apr_status_t spool_reqbody_cl(apr_pool_t *p,
+                                     request_rec *r,
+                                     proxy_http_conn_t *p_conn,
+                                     conn_rec *origin,
+                                     apr_bucket_brigade *header_brigade,
+                                     apr_bucket_brigade *input_brigade,
+                                     int force_cl)
+{
+    int seen_eos = 0;
+    apr_status_t status;
+    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
+    apr_bucket_brigade *body_brigade;
+    apr_bucket *e;
+    apr_off_t bytes, bytes_spooled = 0, fsize = 0;
+    apr_file_t *tmpfile = NULL;
+
+    body_brigade = apr_brigade_create(p, bucket_alloc);
+
+    while (!APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(input_brigade)))
+    {
+        /* If this brigade contains EOS, either stop or remove it. */
+        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
+            seen_eos = 1;
+
+            /* We can't pass this EOS to the output_filters. */
+            e = APR_BRIGADE_LAST(input_brigade);
+            apr_bucket_delete(e);
+        }
+
+        apr_brigade_length(input_brigade, 1, &bytes);
+
+        if (bytes_spooled + bytes > MAX_MEM_SPOOL) {
+            /* can't spool any more in memory; write latest brigade to disk */
+            if (tmpfile == NULL) {
+                const char *temp_dir;
+                char *template;
+
+                status = apr_temp_dir_get(&temp_dir, p);
+                if (status != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                                 "proxy: search for temporary directory failed");
+                    return status;
+                }
+                apr_filepath_merge(&template, temp_dir,
+                                   "modproxy.tmp.XXXXXX",
+                                   APR_FILEPATH_NATIVE, p);
+                status = apr_file_mktemp(&tmpfile, template, 0, p);
+                if (status != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                                 "proxy: creation of temporary file in directory %s failed",
+                                 temp_dir);
+                    return status;
+                }
+            }
+            for (e = APR_BRIGADE_FIRST(input_brigade);
+                 e != APR_BRIGADE_SENTINEL(input_brigade);
+                 e = APR_BUCKET_NEXT(e)) {
+                const char *data;
+                apr_size_t bytes_read, bytes_written;
+
+                apr_bucket_read(e, &data, &bytes_read, APR_BLOCK_READ);
+                status = apr_file_write_full(tmpfile, data, bytes_read, &bytes_written);
+                if (status != APR_SUCCESS) {
+                    const char *tmpfile_name;
+
+                    if (apr_file_name_get(&tmpfile_name, tmpfile) != APR_SUCCESS) {
+                        tmpfile_name = "(unknown)";
+                    }
+                    ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                                 "proxy: write to temporary file %s failed",
+                                 tmpfile_name);
+                    return status;
+                }
+                AP_DEBUG_ASSERT(bytes_read == bytes_written);
+                fsize += bytes_written;
+            }
+            apr_brigade_cleanup(input_brigade);
+        }
+        else {
+            APR_BRIGADE_CONCAT(body_brigade, input_brigade);
+        }
+        
+        bytes_spooled += bytes;
+
+        if (seen_eos) {
+            break;
+        }
+
+        status = ap_get_brigade(r->input_filters, input_brigade,
+                                AP_MODE_READBYTES, APR_BLOCK_READ,
+                                HUGE_STRING_LEN);
+
+        if (status != APR_SUCCESS) {
+            return status;
+        }
+    }
+
+    if (bytes_spooled || force_cl) {
+        add_cl(p, bucket_alloc, header_brigade, apr_off_t_toa(p, bytes_spooled));
+    }
+    terminate_headers(bucket_alloc, header_brigade);
+    APR_BRIGADE_CONCAT(header_brigade, body_brigade);
+    if (tmpfile) {
+        /* For platforms where the size of the file may be larger than
+         * that which can be stored in a single bucket (where the
+         * length field is an apr_size_t), split it into several
+         * buckets: */
+        if (sizeof(apr_off_t) > sizeof(apr_size_t)
+            && fsize > AP_MAX_SENDFILE) {
+            e = apr_bucket_file_create(tmpfile, 0, AP_MAX_SENDFILE, p,
+                                       bucket_alloc);
+            while (fsize > AP_MAX_SENDFILE) {
+                apr_bucket *ce;
+                apr_bucket_copy(e, &ce);
+                APR_BRIGADE_INSERT_TAIL(header_brigade, ce);
+                e->start += AP_MAX_SENDFILE;
+                fsize -= AP_MAX_SENDFILE;
+            }
+            e->length = (apr_size_t)fsize; /* Resize just the last bucket */
+        }
+        else {
+            e = apr_bucket_file_create(tmpfile, 0, (apr_size_t)fsize, p,
+                                       bucket_alloc);
+        }
+        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+    }
+    /* This is all a single brigade, pass with flush flagged */
+    status = pass_brigade(bucket_alloc, r, p_conn, origin, header_brigade, 1);
+    return status;
+}
+
 static
 apr_status_t ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                    proxy_http_conn_t *p_conn, conn_rec *origin, 
                                    proxy_server_conf *conf,
                                    apr_uri_t *uri,
-                                   char *url, apr_bucket_brigade *bb,
-                                   char *server_portstr) {
+                                   char *url, 
+                                   apr_bucket_brigade *header_brigade,
+                                   char *server_portstr) 
+{
     conn_rec *c = r->connection;
-    char *buf;
+    apr_bucket_alloc_t *bucket_alloc = c->bucket_alloc;
+    apr_bucket_brigade *input_brigade;
+    apr_bucket_brigade *temp_brigade;
     apr_bucket *e;
+    char *buf;
     const apr_array_header_t *headers_in_array;
     const apr_table_entry_t *headers_in;
-    int counter, seen_eos;
+    int counter;
     apr_status_t status;
+    enum rb_methods {RB_INIT, RB_STREAM_CL, RB_STREAM_CHUNKED, RB_SPOOL_CL};
+    enum rb_methods rb_method = RB_INIT;
+    const char *old_cl_val = NULL;
+    const char *old_te_val = NULL;
+    apr_off_t bytes_read = 0;
+    apr_off_t bytes;
+    int force10;
 
     /*
      * Send the HTTP/1.1 request to the remote server
      */
 
     /* strip connection listed hop-by-hop headers from the request */
     /* even though in theory a connection: close coming from the client
      * should not affect the connection to the server, it's unlikely
-     * that subsequent client requests will hit this thread/process, so
-     * we cancel server keepalive if the client does.
+     * that subsequent client requests will hit this thread/process, 
+     * so we cancel server keepalive if the client does.
      */
-    p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_in,
-                                                     "Connection"), "close");
-    /* sub-requests never use keepalives */
-    if (r->main) {
+    if (ap_proxy_liststr(apr_table_get(r->headers_in,
+                         "Connection"), "close")) {
         p_conn->close++;
+        /* XXX: we are abusing r->headers_in rather than a copy,
+         * give the core output handler a clue the client would
+         * rather just close.
+         */
+        c->keepalive = AP_CONN_CLOSE;
     }
-
     ap_proxy_clear_connection(p, r->headers_in);
-    if (p_conn->close) {
-        apr_table_setn(r->headers_in, "Connection", "close");
-        origin->keepalive = AP_CONN_CLOSE;
-    }
 
-    if ( apr_table_get(r->subprocess_env,"force-proxy-request-1.0")) {
+    if (apr_table_get(r->subprocess_env, "force-proxy-request-1.0")) {
         buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.0" CRLF, NULL);
+        force10 = 1;
+        p_conn->close++;
     } else {
         buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.1" CRLF, NULL);
+        force10 = 0;
     }
-    if ( apr_table_get(r->subprocess_env,"proxy-nokeepalive")) {
-        apr_table_unset(r->headers_in, "Connection");
+    if (apr_table_get(r->subprocess_env, "proxy-nokeepalive")) {
         origin->keepalive = AP_CONN_CLOSE;
+        p_conn->close++;
     }
     ap_xlate_proto_to_ascii(buf, strlen(buf));
     e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(bb, e);
-    if ( conf->preserve_host == 0 ) {
+    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+    if (conf->preserve_host == 0) {
         if (uri->port_str && uri->port != DEFAULT_HTTP_PORT) {
-            buf = apr_pstrcat(p, "Host: ", uri->hostname, ":", uri->port_str, CRLF,
-                            NULL);
+            buf = apr_pstrcat(p, "Host: ", uri->hostname, ":", uri->port_str,
+                              CRLF, NULL);
         } else {
             buf = apr_pstrcat(p, "Host: ", uri->hostname, CRLF, NULL);
         }
     } 
     else {
         /* don't want to use r->hostname, as the incoming header might have a 
