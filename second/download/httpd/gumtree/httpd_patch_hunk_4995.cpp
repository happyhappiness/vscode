     apr_bucket_alloc_t *bucket_alloc = c->bucket_alloc;
     apr_bucket_brigade *header_brigade;
     apr_bucket_brigade *input_brigade;
     apr_bucket_brigade *temp_brigade;
     apr_bucket *e;
     char *buf;
-    const apr_array_header_t *headers_in_array;
-    const apr_table_entry_t *headers_in;
-    int counter;
     apr_status_t status;
     enum rb_methods {RB_INIT, RB_STREAM_CL, RB_STREAM_CHUNKED, RB_SPOOL_CL};
     enum rb_methods rb_method = RB_INIT;
-    const char *old_cl_val = NULL;
-    const char *old_te_val = NULL;
+    char *old_cl_val = NULL;
+    char *old_te_val = NULL;
     apr_off_t bytes_read = 0;
     apr_off_t bytes;
     int force10, rv;
-    apr_table_t *headers_in_copy;
-    proxy_dir_conf *dconf;
     conn_rec *origin = p_conn->connection;
-    int do_100_continue;
-
-    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
-    header_brigade = apr_brigade_create(p, origin->bucket_alloc);
-
-    /*
-     * Send the HTTP/1.1 request to the remote server
-     */
-
-    /*
-     * To be compliant, we only use 100-Continue for requests with bodies.
-     * We also make sure we won't be talking HTTP/1.0 as well.
-     */
-    do_100_continue = (worker->s->ping_timeout_set
-                       && ap_request_has_body(r)
-                       && (PROXYREQ_REVERSE == r->proxyreq)
-                       && !(apr_table_get(r->subprocess_env, "force-proxy-request-1.0")));
 
     if (apr_table_get(r->subprocess_env, "force-proxy-request-1.0")) {
-        /*
-         * According to RFC 2616 8.2.3 we are not allowed to forward an
-         * Expect: 100-continue to an HTTP/1.0 server. Instead we MUST return
-         * a HTTP_EXPECTATION_FAILED
-         */
         if (r->expecting_100) {
             return HTTP_EXPECTATION_FAILED;
         }
-        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.0" CRLF, NULL);
         force10 = 1;
-        p_conn->close = 1;
     } else {
-        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.1" CRLF, NULL);
         force10 = 0;
     }
-    if (apr_table_get(r->subprocess_env, "proxy-nokeepalive")) {
-        origin->keepalive = AP_CONN_CLOSE;
-        p_conn->close = 1;
-    }
-    ap_xlate_proto_to_ascii(buf, strlen(buf));
-    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
-    if (dconf->preserve_host == 0) {
-        if (ap_strchr_c(uri->hostname, ':')) { /* if literal IPv6 address */
-            if (uri->port_str && uri->port != DEFAULT_HTTP_PORT) {
-                buf = apr_pstrcat(p, "Host: [", uri->hostname, "]:",
-                                  uri->port_str, CRLF, NULL);
-            } else {
-                buf = apr_pstrcat(p, "Host: [", uri->hostname, "]", CRLF, NULL);
-            }
-        } else {
-            if (uri->port_str && uri->port != DEFAULT_HTTP_PORT) {
-                buf = apr_pstrcat(p, "Host: ", uri->hostname, ":",
-                                  uri->port_str, CRLF, NULL);
-            } else {
-                buf = apr_pstrcat(p, "Host: ", uri->hostname, CRLF, NULL);
-            }
-        }
-    }
-    else {
-        /* don't want to use r->hostname, as the incoming header might have a
-         * port attached
-         */
-        const char* hostname = apr_table_get(r->headers_in,"Host");
-        if (!hostname) {
-            hostname =  r->server->server_hostname;
-            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01092)
-                          "no HTTP 0.9 request (with no host line) "
-                          "on incoming request and preserve host set "
-                          "forcing hostname to be %s for uri %s",
-                          hostname, r->uri);
-        }
-        buf = apr_pstrcat(p, "Host: ", hostname, CRLF, NULL);
-    }
-    ap_xlate_proto_to_ascii(buf, strlen(buf));
-    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
-
-    /* handle Via */
-    if (conf->viaopt == via_block) {
-        /* Block all outgoing Via: headers */
-        apr_table_unset(r->headers_in, "Via");
-    } else if (conf->viaopt != via_off) {
-        const char *server_name = ap_get_server_name(r);
-        /* If USE_CANONICAL_NAME_OFF was configured for the proxy virtual host,
-         * then the server name returned by ap_get_server_name() is the
-         * origin server name (which does make too much sense with Via: headers)
-         * so we use the proxy vhost's name instead.
-         */
-        if (server_name == r->hostname)
-            server_name = r->server->server_hostname;
-        /* Create a "Via:" request header entry and merge it */
-        /* Generate outgoing Via: header with/without server comment: */
-        apr_table_mergen(r->headers_in, "Via",
-                         (conf->viaopt == via_full)
-                         ? apr_psprintf(p, "%d.%d %s%s (%s)",
-                                        HTTP_VERSION_MAJOR(r->proto_num),
-                                        HTTP_VERSION_MINOR(r->proto_num),
-                                        server_name, server_portstr,
-                                        AP_SERVER_BASEVERSION)
-                         : apr_psprintf(p, "%d.%d %s%s",
-                                        HTTP_VERSION_MAJOR(r->proto_num),
-                                        HTTP_VERSION_MINOR(r->proto_num),
-                                        server_name, server_portstr)
-        );
-    }
-
-    /* Use HTTP/1.1 100-Continue as quick "HTTP ping" test
-     * to backend
-     */
-    if (do_100_continue) {
-        apr_table_mergen(r->headers_in, "Expect", "100-Continue");
-        r->expecting_100 = 1;
-    }
-
-    /* X-Forwarded-*: handling
-     *
-     * XXX Privacy Note:
-     * -----------------
-     *
-     * These request headers are only really useful when the mod_proxy
-     * is used in a reverse proxy configuration, so that useful info
-     * about the client can be passed through the reverse proxy and on
-     * to the backend server, which may require the information to
-     * function properly.
-     *
-     * In a forward proxy situation, these options are a potential
-     * privacy violation, as information about clients behind the proxy
-     * are revealed to arbitrary servers out there on the internet.
-     *
-     * The HTTP/1.1 Via: header is designed for passing client
-     * information through proxies to a server, and should be used in
-     * a forward proxy configuation instead of X-Forwarded-*. See the
-     * ProxyVia option for details.
-     */
-    if (dconf->add_forwarded_headers) {
-       if (PROXYREQ_REVERSE == r->proxyreq) {
-           const char *buf;
-
-           /* Add X-Forwarded-For: so that the upstream has a chance to
-            * determine, where the original request came from.
-            */
-           apr_table_mergen(r->headers_in, "X-Forwarded-For",
-                            r->useragent_ip);
-
-           /* Add X-Forwarded-Host: so that upstream knows what the
-            * original request hostname was.
-            */
-           if ((buf = apr_table_get(r->headers_in, "Host"))) {
-               apr_table_mergen(r->headers_in, "X-Forwarded-Host", buf);
-           }
-
-           /* Add X-Forwarded-Server: so that upstream knows what the
-            * name of this proxy server is (if there are more than one)
-            * XXX: This duplicates Via: - do we strictly need it?
-            */
-           apr_table_mergen(r->headers_in, "X-Forwarded-Server",
-                            r->server->server_hostname);
-       }
-    }
-
-    proxy_run_fixups(r);
-    /*
-     * Make a copy of the headers_in table before clearing the connection
-     * headers as we need the connection headers later in the http output
-     * filter to prepare the correct response headers.
-     *
-     * Note: We need to take r->pool for apr_table_copy as the key / value
-     * pairs in r->headers_in have been created out of r->pool and
-     * p might be (and actually is) a longer living pool.
-     * This would trigger the bad pool ancestry abort in apr_table_copy if
-     * apr is compiled with APR_POOL_DEBUG.
-     */
-    headers_in_copy = apr_table_copy(r->pool, r->headers_in);
-    ap_proxy_clear_connection(p, headers_in_copy);
-    /* send request headers */
-    headers_in_array = apr_table_elts(headers_in_copy);
-    headers_in = (const apr_table_entry_t *) headers_in_array->elts;
-    for (counter = 0; counter < headers_in_array->nelts; counter++) {
-        if (headers_in[counter].key == NULL
-             || headers_in[counter].val == NULL
-
-            /* Already sent */
-             || !strcasecmp(headers_in[counter].key, "Host")
-
-            /* Clear out hop-by-hop request headers not to send
-             * RFC2616 13.5.1 says we should strip these headers
-             */
-             || !strcasecmp(headers_in[counter].key, "Keep-Alive")
-             || !strcasecmp(headers_in[counter].key, "TE")
-             || !strcasecmp(headers_in[counter].key, "Trailer")
-             || !strcasecmp(headers_in[counter].key, "Upgrade")
-
-             ) {
-            continue;
-        }
-        /* Do we want to strip Proxy-Authorization ?
-         * If we haven't used it, then NO
-         * If we have used it then MAYBE: RFC2616 says we MAY propagate it.
-         * So let's make it configurable by env.
-         */
-        if (!strcasecmp(headers_in[counter].key,"Proxy-Authorization")) {
-            if (r->user != NULL) { /* we've authenticated */
-                if (!apr_table_get(r->subprocess_env, "Proxy-Chain-Auth")) {
-                    continue;
-                }
-            }
-        }
-
-
-        /* Skip Transfer-Encoding and Content-Length for now.
-         */
-        if (!strcasecmp(headers_in[counter].key, "Transfer-Encoding")) {
-            old_te_val = headers_in[counter].val;
-            continue;
-        }
-        if (!strcasecmp(headers_in[counter].key, "Content-Length")) {
-            old_cl_val = headers_in[counter].val;
-            continue;
-        }
 
-        /* for sub-requests, ignore freshness/expiry headers */
-        if (r->main) {
-            if (    !strcasecmp(headers_in[counter].key, "If-Match")
-                 || !strcasecmp(headers_in[counter].key, "If-Modified-Since")
-                 || !strcasecmp(headers_in[counter].key, "If-Range")
-                 || !strcasecmp(headers_in[counter].key, "If-Unmodified-Since")
-                 || !strcasecmp(headers_in[counter].key, "If-None-Match")) {
-                continue;
-            }
-        }
-
-        buf = apr_pstrcat(p, headers_in[counter].key, ": ",
-                          headers_in[counter].val, CRLF,
-                          NULL);
-        ap_xlate_proto_to_ascii(buf, strlen(buf));
-        e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
-        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
+    header_brigade = apr_brigade_create(p, origin->bucket_alloc);
+    rv = ap_proxy_create_hdrbrgd(p, header_brigade, r, p_conn,
+                                 worker, conf, uri, url, server_portstr,
+                                 &old_cl_val, &old_te_val);
+    if (rv != OK) {
+        return rv;
     }
 
     /* We have headers, let's figure out our request body... */
     input_brigade = apr_brigade_create(p, bucket_alloc);
 
     /* sub-requests never use keepalives, and mustn't pass request bodies.
