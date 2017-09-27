             r->server = s;
             return;
         }
     }
 }
 
+static APR_INLINE const char *construct_host_header(request_rec *r,
+                                                    int is_v6literal)
+{
+    struct iovec iov[5];
+    apr_size_t nvec = 0;
+    /*
+     * We cannot use ap_get_server_name/port here, because we must
+     * ignore UseCanonicalName/Port.
+     */
+    if (is_v6literal) {
+        iov[nvec].iov_base = "[";
+        iov[nvec].iov_len = 1;
+        nvec++;
+    }
+    iov[nvec].iov_base = (void *)r->hostname;
+    iov[nvec].iov_len = strlen(r->hostname);
+    nvec++;
+    if (is_v6literal) {
+        iov[nvec].iov_base = "]";
+        iov[nvec].iov_len = 1;
+        nvec++;
+    }
+    if (r->parsed_uri.port_str) {
+        iov[nvec].iov_base = ":";
+        iov[nvec].iov_len = 1;
+        nvec++;
+        iov[nvec].iov_base = r->parsed_uri.port_str;
+        iov[nvec].iov_len = strlen(r->parsed_uri.port_str);
+        nvec++;
+    }
+    return apr_pstrcatv(r->pool, iov, nvec, NULL);
+}
 
 AP_DECLARE(void) ap_update_vhost_from_headers(request_rec *r)
 {
-    /* must set this for HTTP/1.1 support */
-    if (r->hostname || (r->hostname = apr_table_get(r->headers_in, "Host"))) {
-        fix_hostname(r);
-        if (r->status != HTTP_OK)
-            return;
+    core_server_config *conf =
+        (core_server_config *)ap_get_module_config(r->server->module_config,
+                                                   &core_module);
+    const char *host_header = apr_table_get(r->headers_in, "Host");
+    int is_v6literal = 0;
+    int have_hostname_from_url = 0;
+
+    if (r->hostname) {
+        /*
+         * If there was a host part in the Request-URI, ignore the 'Host'
+         * header.
+         */
+        have_hostname_from_url = 1;
+        is_v6literal = fix_hostname(r, NULL, conf->http_conformance);
+    }
+    else if (host_header != NULL) {
+        is_v6literal = fix_hostname(r, host_header, conf->http_conformance);
+    }
+    if (r->status != HTTP_OK)
+        return;
+
+    if (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE) {
+        /*
+         * If we have both hostname from an absoluteURI and a Host header,
+         * we must ignore the Host header (RFC 2616 5.2).
+         * To enforce this, we reset the Host header to the value from the
+         * request line.
+         */
+        if (have_hostname_from_url && host_header != NULL) {
+            const char *repl = construct_host_header(r, is_v6literal);
+            apr_table_set(r->headers_in, "Host", repl);
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                          "Replacing host header '%s' with host '%s' given "
+                          "in the request uri", host_header, repl);
+        }
     }
+
     /* check if we tucked away a name_chain */
     if (r->connection->vhost_lookup_data) {
         if (r->hostname)
             check_hostalias(r);
         else
             check_serverpath(r);
