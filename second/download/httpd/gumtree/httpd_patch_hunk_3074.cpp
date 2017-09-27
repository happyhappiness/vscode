     *urlp = url;
     *hostp = addr;
 
     return NULL;
 }
 
-/*
- * If the date is a valid RFC 850 date or asctime() date, then it
- * is converted to the RFC 1123 format.
- */
-PROXY_DECLARE(const char *)
-     ap_proxy_date_canon(apr_pool_t *p, const char *date)
-{
-    apr_status_t rv;
-    char* ndate;
-
-    apr_time_t time = apr_date_parse_http(date);
-    if (!time) {
-        return date;
-    }
-
-    ndate = apr_palloc(p, APR_RFC822_DATE_LEN);
-    rv = apr_rfc822_date(ndate, time);
-    if (rv != APR_SUCCESS) {
-        return date;
-    }
-
-    return ndate;
-}
-
-PROXY_DECLARE(request_rec *)ap_proxy_make_fake_req(conn_rec *c, request_rec *r)
-{
-    request_rec *rp = apr_pcalloc(r->pool, sizeof(*r));
-
-    rp->pool            = r->pool;
-    rp->status          = HTTP_OK;
-
-    rp->headers_in      = apr_table_make(r->pool, 50);
-    rp->subprocess_env  = apr_table_make(r->pool, 50);
-    rp->headers_out     = apr_table_make(r->pool, 12);
-    rp->err_headers_out = apr_table_make(r->pool, 5);
-    rp->notes           = apr_table_make(r->pool, 5);
-
-    rp->server = r->server;
-    rp->proxyreq = r->proxyreq;
-    rp->request_time = r->request_time;
-    rp->connection      = c;
-    rp->output_filters  = c->output_filters;
-    rp->input_filters   = c->input_filters;
-    rp->proto_output_filters  = c->output_filters;
-    rp->proto_input_filters   = c->input_filters;
-
-    rp->request_config  = ap_create_request_config(r->pool);
-    proxy_run_create_req(r, rp);
-
-    return rp;
-}
-
-
-/*
- * list is a comma-separated list of case-insensitive tokens, with
- * optional whitespace around the tokens.
- * The return returns 1 if the token val is found in the list, or 0
- * otherwise.
- */
-PROXY_DECLARE(int) ap_proxy_liststr(const char *list, const char *val)
-{
-    int len, i;
-    const char *p;
-
-    len = strlen(val);
-
-    while (list != NULL) {
-        p = ap_strchr_c(list, ',');
-        if (p != NULL) {
-            i = p - list;
-            do {
-                p++;
-            } while (apr_isspace(*p));
-        }
-        else {
-            i = strlen(list);
-        }
-
-        while (i > 0 && apr_isspace(list[i - 1])) {
-            i--;
-        }
-        if (i == len && strncasecmp(list, val, len) == 0) {
-            return 1;
-        }
-        list = p;
-    }
-    return 0;
-}
-
-/*
- * list is a comma-separated list of case-insensitive tokens, with
- * optional whitespace around the tokens.
- * if val appears on the list of tokens, it is removed from the list,
- * and the new list is returned.
- */
-PROXY_DECLARE(char *)ap_proxy_removestr(apr_pool_t *pool, const char *list, const char *val)
-{
-    int len, i;
-    const char *p;
-    char *new = NULL;
-
-    len = strlen(val);
-
-    while (list != NULL) {
-        p = ap_strchr_c(list, ',');
-        if (p != NULL) {
-            i = p - list;
-            do {
-                p++;
-            } while (apr_isspace(*p));
-        }
-        else {
-            i = strlen(list);
-        }
-
-        while (i > 0 && apr_isspace(list[i - 1])) {
-            i--;
-        }
-        if (i == len && strncasecmp(list, val, len) == 0) {
-            /* do nothing */
-        }
-        else {
-            if (new) {
-                new = apr_pstrcat(pool, new, ",", apr_pstrndup(pool, list, i), NULL);
-            }
-            else {
-                new = apr_pstrndup(pool, list, i);
-            }
-        }
-        list = p;
-    }
-    return new;
-}
-
-/*
- * Converts 8 hex digits to a time integer
- */
-PROXY_DECLARE(int) ap_proxy_hex2sec(const char *x)
-{
-    int i, ch;
-    unsigned int j;
-
-    for (i = 0, j = 0; i < 8; i++) {
-        ch = x[i];
-        j <<= 4;
-        if (apr_isdigit(ch)) {
-            j |= ch - '0';
-        }
-        else if (apr_isupper(ch)) {
-            j |= ch - ('A' - 10);
-        }
-        else {
-            j |= ch - ('a' - 10);
-        }
-    }
-    if (j == 0xffffffff) {
-        return -1;      /* so that it works with 8-byte ints */
-    }
-    else {
-        return j;
-    }
-}
-
-/*
- * Converts a time integer to 8 hex digits
- */
-PROXY_DECLARE(void) ap_proxy_sec2hex(int t, char *y)
-{
-    int i, ch;
-    unsigned int j = t;
-
-    for (i = 7; i >= 0; i--) {
-        ch = j & 0xF;
-        j >>= 4;
-        if (ch >= 10) {
-            y[i] = ch + ('A' - 10);
-        }
-        else {
-            y[i] = ch + '0';
-        }
-    }
-    y[8] = '\0';
-}
-
 PROXY_DECLARE(int) ap_proxyerror(request_rec *r, int statuscode, const char *message)
 {
+    const char *uri = ap_escape_html(r->pool, r->uri);
     apr_table_setn(r->notes, "error-notes",
-    apr_pstrcat(r->pool,
-        "The proxy server could not handle the request "
-        "<em><a href=\"", ap_escape_html(r->pool, r->uri),
-        "\">", ap_escape_html(r->pool, r->method),
-        "&nbsp;",
-        ap_escape_html(r->pool, r->uri), "</a></em>.<p>\n"
-        "Reason: <strong>",
-        ap_escape_html(r->pool, message),
-        "</strong></p>", NULL));
+        apr_pstrcat(r->pool,
+            "The proxy server could not handle the request <em><a href=\"",
+            uri, "\">", ap_escape_html(r->pool, r->method), "&nbsp;", uri,
+            "</a></em>.<p>\n"
+            "Reason: <strong>", ap_escape_html(r->pool, message),
+            "</strong></p>",
+            NULL));
 
     /* Allow "error-notes" string to be printed by ap_send_error_response() */
     apr_table_setn(r->notes, "verbose-error-to", apr_pstrdup(r->pool, "*"));
 
     r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-             "proxy: %s returned by %s", message, r->uri);
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00898) "%s returned by %s", message,
+                  r->uri);
     return statuscode;
 }
 
 static const char *
      proxy_get_host_of_request(request_rec *r)
 {
