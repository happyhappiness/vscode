         ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                       "Request received from client: %s",
                       ap_escape_logitem(r->pool, r->the_request));
     }
 
     r->request_time = apr_time_now();
-    ll = r->the_request;
-    r->method = ap_getword_white(r->pool, &ll);
 
-    uri = ap_getword_white(r->pool, &ll);
+    r->method = r->the_request;
 
-    if (!*r->method || !*uri) {
-        r->status    = HTTP_BAD_REQUEST;
-        r->proto_num = HTTP_VERSION(1,0);
-        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
-        return 0;
+    /* If there is whitespace before a method, skip it and mark in error */
+    if (apr_isspace(*r->method)) {
+        deferred_error = rrl_badwhitespace; 
+        for ( ; apr_isspace(*r->method); ++r->method)
+            ; 
     }
 
-    /* Provide quick information about the request method as soon as known */
+    /* Scan the method up to the next whitespace, ensure it contains only
+     * valid http-token characters, otherwise mark in error
+     */
+    if (strict) {
+        ll = (char*) ap_scan_http_token(r->method);
+    }
+    else {
+        ll = (char*) ap_scan_vchar_obstext(r->method);
+    }
+
+    if (((ll == r->method) || (*ll && !apr_isspace(*ll)))
+            && deferred_error == rrl_none) {
+        deferred_error = rrl_badmethod;
+        ll = strpbrk(ll, "\t\n\v\f\r ");
+    }
+
+    /* Verify method terminated with a single SP, or mark as specific error */
+    if (!ll) {
+        if (deferred_error == rrl_none)
+            deferred_error = rrl_missinguri;
+        r->protocol = uri = "";
+        len = 0;
+        goto rrl_done;
+    }
+    else if (strict && ll[0] && apr_isspace(ll[1])
+             && deferred_error == rrl_none) {
+        deferred_error = rrl_excesswhitespace; 
+    }
+
+    /* Advance uri pointer over leading whitespace, NUL terminate the method
+     * If non-SP whitespace is encountered, mark as specific error
+     */
+    for (uri = ll; apr_isspace(*uri); ++uri) 
+        if (*uri != ' ' && deferred_error == rrl_none)
+            deferred_error = rrl_badwhitespace; 
+    *ll = '\0';
 
+    if (!*uri && deferred_error == rrl_none)
+        deferred_error = rrl_missinguri;
+
+    /* Scan the URI up to the next whitespace, ensure it contains no raw
+     * control characters, otherwise mark in error
+     */
+    ll = (char*) ap_scan_vchar_obstext(uri);
+    if (ll == uri || (*ll && !apr_isspace(*ll))) {
+        deferred_error = rrl_baduri;
+        ll = strpbrk(ll, "\t\n\v\f\r ");
+    }
+
+    /* Verify URI terminated with a single SP, or mark as specific error */
+    if (!ll) {
+        r->protocol = "";
+        len = 0;
+        goto rrl_done;
+    }
+    else if (strict && ll[0] && apr_isspace(ll[1])
+             && deferred_error == rrl_none) {
+        deferred_error = rrl_excesswhitespace; 
+    }
+
+    /* Advance protocol pointer over leading whitespace, NUL terminate the uri
+     * If non-SP whitespace is encountered, mark as specific error
+     */
+    for (r->protocol = ll; apr_isspace(*r->protocol); ++r->protocol) 
+        if (*r->protocol != ' ' && deferred_error == rrl_none)
+            deferred_error = rrl_badwhitespace; 
+    *ll = '\0';
+
+    /* Scan the protocol up to the next whitespace, validation comes later */
+    if (!(ll = (char*) ap_scan_vchar_obstext(r->protocol))) {
+        len = strlen(r->protocol);
+        goto rrl_done;
+    }
+    len = ll - r->protocol;
+
+    /* Advance over trailing whitespace, if found mark in error,
+     * determine if trailing text is found, unconditionally mark in error,
+     * finally NUL terminate the protocol string
+     */
+    if (*ll && !apr_isspace(*ll)) {
+        deferred_error = rrl_badprotocol;
+    }
+    else if (strict && *ll) {
+        deferred_error = rrl_excesswhitespace;
+    }
+    else {
+        for ( ; apr_isspace(*ll); ++ll)
+            if (*ll != ' ' && deferred_error == rrl_none)
+                deferred_error = rrl_badwhitespace; 
+        if (*ll && deferred_error == rrl_none)
+            deferred_error = rrl_trailingtext;
+    }
+    *((char *)r->protocol + len) = '\0';
+
+rrl_done:
+    /* For internal integrety and palloc efficiency, reconstruct the_request
+     * in one palloc, using only single SP characters, per spec.
+     */
+    r->the_request = apr_pstrcat(r->pool, r->method, *uri ? " " : NULL, uri,
+                                 *r->protocol ? " " : NULL, r->protocol, NULL);
+
+    if (len == 8
+            && r->protocol[0] == 'H' && r->protocol[1] == 'T'
+            && r->protocol[2] == 'T' && r->protocol[3] == 'P'
+            && r->protocol[4] == '/' && apr_isdigit(r->protocol[5])
+            && r->protocol[6] == '.' && apr_isdigit(r->protocol[7])
+            && r->protocol[5] != '0') {
+        r->assbackwards = 0;
+        r->proto_num = HTTP_VERSION(r->protocol[5] - '0', r->protocol[7] - '0');
+    }
+    else if (len == 8
+                 && (r->protocol[0] == 'H' || r->protocol[0] == 'h')
+                 && (r->protocol[1] == 'T' || r->protocol[1] == 't')
+                 && (r->protocol[2] == 'T' || r->protocol[2] == 't')
+                 && (r->protocol[3] == 'P' || r->protocol[3] == 'p')
+                 && r->protocol[4] == '/' && apr_isdigit(r->protocol[5])
+                 && r->protocol[6] == '.' && apr_isdigit(r->protocol[7])
+                 && r->protocol[5] != '0') {
+        r->assbackwards = 0;
+        r->proto_num = HTTP_VERSION(r->protocol[5] - '0', r->protocol[7] - '0');
+        if (strict && deferred_error == rrl_none)
+            deferred_error = rrl_badprotocol;
+        else
+            memcpy((char*)r->protocol, "HTTP", 4);
+    }
+    else if (r->protocol[0]) {
+        r->proto_num = HTTP_VERSION(0, 9);
+        /* Defer setting the r->protocol string till error msg is composed */
+        if (deferred_error == rrl_none)
+            deferred_error = rrl_badprotocol;
+    }
+    else {
+        r->assbackwards = 1;
+        r->protocol  = apr_pstrdup(r->pool, "HTTP/0.9");
+        r->proto_num = HTTP_VERSION(0, 9);
+    }
+
+    /* Determine the method_number and parse the uri prior to invoking error
+     * handling, such that these fields are available for subsitution
+     */
     r->method_number = ap_method_number_of(r->method);
-    if (r->method_number == M_GET && r->method[0] == 'H') {
+    if (r->method_number == M_GET && r->method[0] == 'H')
         r->header_only = 1;
-    }
 
     ap_parse_uri(r, uri);
-    if (r->status != HTTP_OK) {
-        r->proto_num = HTTP_VERSION(1,0);
-        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
+
+    /* With the request understood, we can consider HTTP/0.9 specific errors */
+    if (r->proto_num == HTTP_VERSION(0, 9) && deferred_error == rrl_none) {
+        if (conf->http09_enable == AP_HTTP09_DISABLE)
+            deferred_error = rrl_reject09;
+        else if (strict && (r->method_number != M_GET || r->header_only))
+            deferred_error = rrl_badmethod09;
+    }
+
+    /* Now that the method, uri and protocol are all processed,
+     * we can safely resume any deferred error reporting
+     */
+    if (deferred_error != rrl_none) {
+        if (deferred_error == rrl_badmethod)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03445)
+                          "HTTP Request Line; Invalid method token: '%.*s'",
+                          field_name_len(r->method), r->method);
+        else if (deferred_error == rrl_badmethod09)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03444)
+                          "HTTP Request Line; Invalid method token: '%.*s'"
+                          " (only GET is allowed for HTTP/0.9 requests)",
+                          field_name_len(r->method), r->method);
+        else if (deferred_error == rrl_missinguri)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03446)
+                          "HTTP Request Line; Missing URI");
+        else if (deferred_error == rrl_baduri)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03454)
+                          "HTTP Request Line; URI incorrectly encoded: '%.*s'",
+                          field_name_len(r->uri), r->uri);
+        else if (deferred_error == rrl_badwhitespace)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03447)
+                          "HTTP Request Line; Invalid whitespace");
+        else if (deferred_error == rrl_excesswhitespace)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03448)
+                          "HTTP Request Line; Excess whitespace "
+                          "(disallowed by HttpProtocolOptions Strict");
+        else if (deferred_error == rrl_trailingtext)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03449)
+                          "HTTP Request Line; Extraneous text found '%.*s' "
+                          "(perhaps whitespace was injected?)",
+                          field_name_len(ll), ll);
+        else if (deferred_error == rrl_reject09)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02401)
+                          "HTTP Request Line; Rejected HTTP/0.9 request");
+        else if (deferred_error == rrl_badprotocol)
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02418)
+                          "HTTP Request Line; Unrecognized protocol '%.*s' "
+                          "(perhaps whitespace was injected?)",
+                          field_name_len(r->protocol), r->protocol);
+        r->status = HTTP_BAD_REQUEST;
+        goto rrl_failed;
+    }
+
+    if (conf->http_methods == AP_HTTP_METHODS_REGISTERED
+            && r->method_number == M_INVALID) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02423)
+                      "HTTP Request Line; Unrecognized HTTP method: '%.*s' "
+                      "(disallowed by RegisteredMethods)",
+                      field_name_len(r->method), r->method);
+        r->status = HTTP_NOT_IMPLEMENTED;
+        /* This can't happen in an HTTP/0.9 request, we verified GET above */
         return 0;
     }
 
-    if (ll[0]) {
-        r->assbackwards = 0;
-        pro = ll;
-        len = strlen(ll);
-    } else {
-        r->assbackwards = 1;
-        pro = "HTTP/0.9";
-        len = 8;
+    if (r->status != HTTP_OK) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03450)
+                      "HTTP Request Line; Unable to parse URI: '%.*s'",
+                      field_name_len(r->uri), r->uri);
+        goto rrl_failed;
     }
-    r->protocol = apr_pstrmemdup(r->pool, pro, len);
 
-    /* Avoid sscanf in the common case */
-    if (len == 8
-        && pro[0] == 'H' && pro[1] == 'T' && pro[2] == 'T' && pro[3] == 'P'
-        && pro[4] == '/' && apr_isdigit(pro[5]) && pro[6] == '.'
-        && apr_isdigit(pro[7])) {
-        r->proto_num = HTTP_VERSION(pro[5] - '0', pro[7] - '0');
-    }
-    else if (3 == sscanf(r->protocol, "%4s/%u.%u", http, &major, &minor)
-             && (strcasecmp("http", http) == 0)
-             && (minor < HTTP_VERSION(1, 0)) ) /* don't allow HTTP/0.1000 */
-        r->proto_num = HTTP_VERSION(major, minor);
-    else
-        r->proto_num = HTTP_VERSION(1, 0);
+    if (strict) {
+        if (r->parsed_uri.fragment) {
+            /* RFC3986 3.5: no fragment */
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02421)
+                          "HTTP Request Line; URI must not contain a fragment");
+            r->status = HTTP_BAD_REQUEST;
+            goto rrl_failed;
+        }
+        if (r->parsed_uri.user || r->parsed_uri.password) {
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02422)
+                          "HTTP Request Line; URI must not contain a "
+                          "username/password");
+            r->status = HTTP_BAD_REQUEST;
+            goto rrl_failed;
+        }
+    }
 
     return 1;
+
+rrl_failed:
+    if (r->proto_num == HTTP_VERSION(0, 9)) {
+        /* Send all parsing and protocol error response with 1.x behavior,
+         * and reserve 505 errors for actual HTTP protocols presented.
+         * As called out in RFC7230 3.5, any errors parsing the protocol
+         * from the request line are nearly always misencoded HTTP/1.x
+         * requests. Only a valid 0.9 request with no parsing errors
+         * at all may be treated as a simple request, if allowed.
+         */
+        r->assbackwards = 0;
+        r->connection->keepalive = AP_CONN_CLOSE;
+        r->proto_num = HTTP_VERSION(1, 0);
+        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
+    }
+    return 0;
 }
 
 static int table_do_fn_check_lengths(void *r_, const char *key,
                                      const char *value)
 {
     request_rec *r = r_;
     if (value == NULL || r->server->limit_req_fieldsize >= strlen(value) )
         return 1;
 
     r->status = HTTP_BAD_REQUEST;
     apr_table_setn(r->notes, "error-notes",
-                   apr_pstrcat(r->pool, "Size of a request header field "
-                               "after merging exceeds server limit.<br />"
-                               "\n<pre>\n",
-                               ap_escape_html(r->pool, key),
-                               "</pre>\n", NULL));
-    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00560) "Request header "
-                  "exceeds LimitRequestFieldSize after merging: %s", key);
+                   "Size of a request header field exceeds server limit.");
+    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00560) "Request "
+                  "header exceeds LimitRequestFieldSize after merging: %.*s",
+                  field_name_len(key), key);
     return 0;
 }
 
-/* get the length of the field name for logging, but no more than 80 bytes */
-#define LOG_NAME_MAX_LEN 80
-static int field_name_len(const char *field)
-{
-    const char *end = ap_strchr_c(field, ':');
-    if (end == NULL || end - field > LOG_NAME_MAX_LEN)
-        return LOG_NAME_MAX_LEN;
-    return end - field;
-}
-
 AP_DECLARE(void) ap_get_mime_headers_core(request_rec *r, apr_bucket_brigade *bb)
 {
     char *last_field = NULL;
     apr_size_t last_len = 0;
     apr_size_t alloc_len = 0;
     char *field;
     char *value;
     apr_size_t len;
     int fields_read = 0;
     char *tmp_field;
+    core_server_config *conf = ap_get_core_module_config(r->server->module_config);
+    int strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
 
     /*
      * Read header lines until we get the empty separator line, a read error,
      * the connection closes (EOF), reach the server limit, or we timeout.
      */
     while(1) {
         apr_status_t rv;
-        int folded = 0;
 
         field = NULL;
         rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
-                         &len, r, 0, bb);
+                         &len, r, strict ? AP_GETLINE_CRLF : 0, bb);
 
         if (rv != APR_SUCCESS) {
             if (APR_STATUS_IS_TIMEUP(rv)) {
                 r->status = HTTP_REQUEST_TIME_OUT;
             }
             else {
