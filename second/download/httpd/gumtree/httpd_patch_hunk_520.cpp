 
         /* Add X-Forwarded-Server: so that upstream knows what the
          * name of this proxy server is (if there are more than one)
          * XXX: This duplicates Via: - do we strictly need it?
          */
         apr_table_mergen(r->headers_in, "X-Forwarded-Server",
-                       r->server->server_hostname);
+                         r->server->server_hostname);
     }
 
     /* send request headers */
     proxy_run_fixups(r);
     headers_in_array = apr_table_elts(r->headers_in);
     headers_in = (const apr_table_entry_t *) headers_in_array->elts;
     for (counter = 0; counter < headers_in_array->nelts; counter++) {
-        if (headers_in[counter].key == NULL || headers_in[counter].val == NULL
+        if (headers_in[counter].key == NULL 
+             || headers_in[counter].val == NULL
 
-        /* Clear out hop-by-hop request headers not to send
-         * RFC2616 13.5.1 says we should strip these headers
-         */
-                /* Already sent */
-            || !apr_strnatcasecmp(headers_in[counter].key, "Host")
+            /* Already sent */
+             || !strcasecmp(headers_in[counter].key, "Host")
 
-            || !apr_strnatcasecmp(headers_in[counter].key, "Keep-Alive")
-            || !apr_strnatcasecmp(headers_in[counter].key, "TE")
-            || !apr_strnatcasecmp(headers_in[counter].key, "Trailer")
-            || !apr_strnatcasecmp(headers_in[counter].key, "Transfer-Encoding")
-            || !apr_strnatcasecmp(headers_in[counter].key, "Upgrade")
-
-        /* XXX: @@@ FIXME: "Proxy-Authorization" should *only* be 
-         * suppressed if THIS server requested the authentication,
-         * not when a frontend proxy requested it!
-         *
-         * The solution to this problem is probably to strip out
-         * the Proxy-Authorisation header in the authorisation
-         * code itself, not here. This saves us having to signal
-         * somehow whether this request was authenticated or not.
+            /* Clear out hop-by-hop request headers not to send
+             * RFC2616 13.5.1 says we should strip these headers
+             */
+             || !strcasecmp(headers_in[counter].key, "Keep-Alive")
+             || !strcasecmp(headers_in[counter].key, "TE")
+             || !strcasecmp(headers_in[counter].key, "Trailer")
+             || !strcasecmp(headers_in[counter].key, "Upgrade")
+
+            /* XXX: @@@ FIXME: "Proxy-Authorization" should *only* be 
+             * suppressed if THIS server requested the authentication,
+             * not when a frontend proxy requested it!
+             *
+             * The solution to this problem is probably to strip out
+             * the Proxy-Authorisation header in the authorisation
+             * code itself, not here. This saves us having to signal
+             * somehow whether this request was authenticated or not.
+             */
+             || !strcasecmp(headers_in[counter].key,"Proxy-Authorization")
+             || !strcasecmp(headers_in[counter].key,"Proxy-Authenticate")) {
+            continue;
+        }
+
+        /* Skip Transfer-Encoding and Content-Length for now.
          */
-            || !apr_strnatcasecmp(headers_in[counter].key,"Proxy-Authorization")
-            || !apr_strnatcasecmp(headers_in[counter].key,"Proxy-Authenticate")) {
+        if (!strcasecmp(headers_in[counter].key, "Transfer-Encoding")) {
+            old_te_val = headers_in[counter].val;
+            continue;
+        }
+        if (!strcasecmp(headers_in[counter].key, "Content-Length")) {
+            old_cl_val = headers_in[counter].val;
             continue;
         }
+
         /* for sub-requests, ignore freshness/expiry headers */
         if (r->main) {
-                if (headers_in[counter].key == NULL || headers_in[counter].val == NULL
-                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Match")
-                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Modified-Since")
-                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Range")
-                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Unmodified-Since")                     
-                     || !apr_strnatcasecmp(headers_in[counter].key, "If-None-Match")) {
-                    continue;
-                }
-
-                /* If you POST to a page that gets server-side parsed
-                 * by mod_include, and the parsing results in a reverse
-                 * proxy call, the proxied request will be a GET, but
-                 * its request_rec will have inherited the Content-Length
-                 * of the original request (the POST for the enclosing
-                 * page).  We can't send the original POST's request body
-                 * as part of the proxied subrequest, so we need to avoid
-                 * sending the corresponding content length.  Otherwise,
-                 * the server to which we're proxying will sit there
-                 * forever, waiting for a request body that will never
-                 * arrive.
-                 */
-                if ((r->method_number == M_GET) && headers_in[counter].key &&
-                    !apr_strnatcasecmp(headers_in[counter].key,
-                                       "Content-Length")) {
-                    continue;
-                }
+            if (    !strcasecmp(headers_in[counter].key, "If-Match")
+                 || !strcasecmp(headers_in[counter].key, "If-Modified-Since")
+                 || !strcasecmp(headers_in[counter].key, "If-Range")
+                 || !strcasecmp(headers_in[counter].key, "If-Unmodified-Since")
+                 || !strcasecmp(headers_in[counter].key, "If-None-Match")) {
+                continue;
+            }
         }
 
-
         buf = apr_pstrcat(p, headers_in[counter].key, ": ",
                           headers_in[counter].val, CRLF,
                           NULL);
         ap_xlate_proto_to_ascii(buf, strlen(buf));
         e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bb, e);
+        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
     }
 
-    /* add empty line at the end of the headers */
-#if APR_CHARSET_EBCDIC
-    e = apr_bucket_immortal_create("\015\012", 2, c->bucket_alloc);
-#else
-    e = apr_bucket_immortal_create(CRLF, sizeof(CRLF)-1, c->bucket_alloc);
-#endif
-    APR_BRIGADE_INSERT_TAIL(bb, e);
-    e = apr_bucket_flush_create(c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(bb, e);
+    /* We have headers, let's figure out our request body... */
+    input_brigade = apr_brigade_create(p, bucket_alloc);
 
-    status = ap_pass_brigade(origin->output_filters, bb);
+    /* sub-requests never use keepalives, and mustn't pass request bodies.
+     * Because the new logic looks at input_brigade, we will self-terminate
+     * input_brigade and jump past all of the request body logic...
+     * Reading anything with ap_get_brigade is likely to consume the
+     * main request's body or read beyond EOS - which would be unplesant.
+     */
+    if (r->main) {
+        p_conn->close++;
+        if (old_cl_val) {
+            old_cl_val = NULL;
+            apr_table_unset(r->headers_in, "Content-Length");
+        }
+        if (old_te_val) {
+            old_te_val = NULL;
+            apr_table_unset(r->headers_in, "Transfer-Encoding");
+        }
+        rb_method = RB_STREAM_CL;
+        e = apr_bucket_eos_create(input_brigade->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(input_brigade, e);
+        goto skip_body;
+    }
 
-    if (status != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
-                     "proxy: request failed to %pI (%s)",
-                     p_conn->addr, p_conn->name);
-        return status;
+    /* WE only understand chunked.  Other modules might inject
+     * (and therefore, decode) other flavors but we don't know
+     * that the can and have done so unless they they remove
+     * their decoding from the headers_in T-E list.
+     * XXX: Make this extensible, but in doing so, presume the
+     * encoding has been done by the extensions' handler, and 
+     * do not modify add_te_chunked's logic
+     */
+    if (old_te_val && strcmp(old_te_val, "chunked") != 0) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+                     "proxy: %s Transfer-Encoding is not supported",
+                     old_te_val);
+        return APR_EINVAL;
     }
 
-    /* send the request data, if any. */
-    seen_eos = 0;
-    do {
-        status = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
-                                APR_BLOCK_READ, HUGE_STRING_LEN);
+    if (old_cl_val && old_te_val) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_ENOTIMPL, r->server,
+                     "proxy: client %s (%s) requested Transfer-Encoding body"
+                     " with Content-Length (C-L ignored)",
+                     c->remote_ip, c->remote_host ? c->remote_host: "");
+        apr_table_unset(r->headers_in, "Content-Length");
+        old_cl_val = NULL;
+        origin->keepalive = AP_CONN_CLOSE;
+        p_conn->close++;
+    }
 
+    /* Prefetch MAX_MEM_SPOOL bytes
+     *
+     * This helps us avoid any election of C-L v.s. T-E
+     * request bodies, since we are willing to keep in
+     * memory this much data, in any case.  This gives
+     * us an instant C-L election if the body is of some
+     * reasonable size.
+     */
+    temp_brigade = apr_brigade_create(p, bucket_alloc);
+    do {
+        status = ap_get_brigade(r->input_filters, temp_brigade,
+                                AP_MODE_READBYTES, APR_BLOCK_READ,
+                                MAX_MEM_SPOOL - bytes_read);
         if (status != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                         "proxy: prefetch request body failed to %s"
+                         " from %s (%s)",
+                         p_conn->name ? p_conn->name: "",
+                         c->remote_ip, c->remote_host ? c->remote_host: "");
             return status;
         }
 
-        /* If this brigade contain EOS, either stop or remove it. */
-        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
-            /* As a shortcut, if this brigade is simply an EOS bucket,
-             * don't send anything down the filter chain.
-             */
-            if (APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(bb))) {
-                break;
-            }
+        apr_brigade_length(temp_brigade, 1, &bytes);
+        APR_BRIGADE_CONCAT(input_brigade, temp_brigade);
+        bytes_read += bytes;
+
+    /* Ensure we don't hit a wall where we have a buffer too small
+     * for ap_get_brigade's filters to fetch us another bucket,
+     * surrender once we hit 80 bytes less than MAX_MEM_SPOOL
+     * (an arbitrary value.)
+     */
+    } while ((bytes_read < MAX_MEM_SPOOL - 80) 
+              && !APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade)));
 
-            /* We can't pass this EOS to the output_filters. */
-            e = APR_BRIGADE_LAST(bb);
-            apr_bucket_delete(e);
-            seen_eos = 1;
+    /* Use chunked request body encoding or send a content-length body?
+     *
+     * Prefer C-L when:
+     *
+     *   We have no request body (handled by RB_STREAM_CL)
+     *
+     *   We have a request body length <= MAX_MEM_SPOOL 
+     *
+     *   The administrator has setenv force-proxy-request-1.0
+     *   
+     *   The client sent a C-L body, and the administrator has
+     *   not setenv proxy-sendchunked or has set setenv proxy-sendcl
+     *
+     *   The client sent a T-E body, and the administrator has
+     *   setenv proxy-sendcl, and not setenv proxy-sendchunked
+     *
+     * If both proxy-sendcl and proxy-sendchunked are set, the
+     * behavior is the same as if neither were set, large bodies
+     * that can't be read will be forwarded in their original
+     * form of C-L, or T-E.
+     *
+     * To ensure maximum compatibility, setenv proxy-sendcl
+     * To reduce server resource use,   setenv proxy-sendchunked
+     *
+     * Then address specific servers with conditional setenv
+     * options to restore the default behavior where desireable.
+     *
+     * We have to compute content length by reading the entire request
+     * body; if request body is not small, we'll spool the remaining
+     * input to a temporary file.  Chunked is always preferable.
+     *
+     * We can only trust the client-provided C-L if the T-E header
+     * is absent, and the filters are unchanged (the body won't 
+     * be resized by another content filter).
+     */
+    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
+        /* The whole thing fit, so our decision is trivial, use
+         * the filtered bytes read from the client for the request 
+         * body Content-Length.
+         *
+         * If we expected no body, and read no body, do not set
+         * the Content-Length.
+         */
+        if (old_cl_val || old_te_val || bytes_read) {
+            old_cl_val = apr_off_t_toa(r->pool, bytes_read);
         }
+        rb_method = RB_STREAM_CL;
+    }
+    else if (old_te_val) {
+        if (force10 
+             || (apr_table_get(r->subprocess_env, "proxy-sendcl")
+                  && !apr_table_get(r->subprocess_env, "proxy-sendchunks"))) {
+            rb_method = RB_SPOOL_CL;
+        }
+        else {
+            rb_method = RB_STREAM_CHUNKED;
+        }
+    }
+    else if (old_cl_val) {
+        if (r->input_filters == r->proto_input_filters) {
+            rb_method = RB_STREAM_CL;
+        }
+        else if (!force10 
+                  && apr_table_get(r->subprocess_env, "proxy-sendchunks")
+                  && !apr_table_get(r->subprocess_env, "proxy-sendcl")) {
+            rb_method = RB_STREAM_CHUNKED;
+        }
+        else {
+            rb_method = RB_SPOOL_CL;
+        }
+    }
+    else {
+        /* This is an appropriate default; very efficient for no-body
+         * requests, and has the behavior that it will not add any C-L
+         * when the old_cl_val is NULL.
+         */
+        rb_method = RB_SPOOL_CL;
+    }
 
-        e = apr_bucket_flush_create(c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(bb, e);
+/* Yes I hate gotos.  This is the subrequest shortcut */
+skip_body:
+    /* Handle Connection: header */
+    if (!force10 && p_conn->close) {
+        buf = apr_pstrdup(p, "Connection: close" CRLF);
+        ap_xlate_proto_to_ascii(buf, strlen(buf));
+        e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+    }
 
-        status = ap_pass_brigade(origin->output_filters, bb);
-        if (status != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
-                         "proxy: pass request data failed to %pI (%s)",
-                         p_conn->addr, p_conn->name);
-            return status;
-        }
-        apr_brigade_cleanup(bb);
-    } while (!seen_eos);
+    /* send the request body, if any. */
+    switch(rb_method) {
+    case RB_STREAM_CHUNKED:
+        status = stream_reqbody_chunked(p, r, p_conn, origin, header_brigade, 
+                                        input_brigade);
+        break;
+    case RB_STREAM_CL:
+        status = stream_reqbody_cl(p, r, p_conn, origin, header_brigade, 
+                                   input_brigade, old_cl_val);
+        break;
+    case RB_SPOOL_CL:
+        status = spool_reqbody_cl(p, r, p_conn, origin, header_brigade,
+                                  input_brigade, (old_cl_val != NULL)
+                                              || (old_te_val != NULL)
+                                              || (bytes_read > 0));
+        break;
+    default:
+        ap_assert(1 != 1);
+        break;
+    }
+
+    if (status != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
+                     "proxy: pass request body failed to %pI (%s)"
+                     " from %s (%s)",
+                     p_conn->addr, p_conn->name ? p_conn->name: "",
+                     c->remote_ip, c->remote_host ? c->remote_host: "");
+        return status;
+    }
 
     return APR_SUCCESS;
 }
 
 static
 apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
