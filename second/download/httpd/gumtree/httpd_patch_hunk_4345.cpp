 
     } while (again);
 
     return APR_SUCCESS;
 }
 
+struct check_header_ctx {
+    request_rec *r;
+    int strict;
+};
+
+/* check a single header, to be used with apr_table_do() */
+static int check_header(void *arg, const char *name, const char *val)
+{
+    struct check_header_ctx *ctx = arg;
+    const char *test;
+
+    if (name[0] == '\0') {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02428)
+                      "Empty response header name, aborting request");
+        return 0;
+    }
+
+    if (ctx->strict) { 
+        test = ap_scan_http_token(name);
+    }
+    else {
+        test = ap_scan_vchar_obstext(name);
+    }
+    if (*test) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02429)
+                      "Response header name '%s' contains invalid "
+                      "characters, aborting request",
+                      name);
+        return 0;
+    }
+
+    test = ap_scan_http_field_content(val);
+    if (*test) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02430)
+                      "Response header '%s' value of '%s' contains invalid "
+                      "characters, aborting request",
+                      name, val);
+        return 0;
+    }
+    return 1;
+}
+
+/**
+ * Check headers for HTTP conformance
+ * @return 1 if ok, 0 if bad
+ */
+static APR_INLINE int check_headers(request_rec *r)
+{
+    struct check_header_ctx ctx;
+    core_server_config *conf =
+            ap_get_core_module_config(r->server->module_config);
+
+    ctx.r = r;
+    ctx.strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
+    return apr_table_do(check_header, &ctx, r->headers_out, NULL) &&
+           apr_table_do(check_header, &ctx, r->err_headers_out, NULL);
+}
+
+static int check_headers_recursion(request_rec *r)
+{
+    void *check = NULL;
+    apr_pool_userdata_get(&check, "check_headers_recursion", r->pool);
+    if (check) {
+        return 1;
+    }
+    apr_pool_userdata_setn("true", "check_headers_recursion", NULL, r->pool);
+    return 0;
+}
+
 typedef struct header_struct {
     apr_pool_t *pool;
     apr_bucket_brigade *bb;
 } header_struct;
 
 /* Send a single HTTP header field to the client.  Note that this function
- * is used in calls to table_do(), so their interfaces are co-dependent.
- * In other words, don't change this one without checking table_do in alloc.c.
+ * is used in calls to apr_table_do(), so don't change its interface.
  * It returns true unless there was a write error of some kind.
  */
 static int form_header_field(header_struct *h,
                              const char *fieldname, const char *fieldval)
 {
 #if APR_CHARSET_EBCDIC
