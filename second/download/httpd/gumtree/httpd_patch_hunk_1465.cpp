 
     } while (again);
 
     return APR_SUCCESS;
 }
 
+struct check_header_ctx {
+    request_rec *r;
+    int strict;
+};
+
+/* check a single header, to be used with apr_table_do() */
+static int check_header(struct check_header_ctx *ctx,
+                        const char *name, const char **val)
+{
+    const char *pos, *end;
+    char *dst = NULL;
+
+    if (name[0] == '\0') {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
+                      "Empty response header name, aborting request");
+        return 0;
+    }
+
+    if (ctx->strict) { 
+        end = ap_scan_http_token(name);
+    }
+    else {
+        end = ap_scan_vchar_obstext(name);
+    }
+    if (*end) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
+                      "Response header name '%s' contains invalid "
+                      "characters, aborting request",
+                      name);
+        return 0;
+    }
+
+    for (pos = *val; *pos; pos = end) {
+        end = ap_scan_http_field_content(pos);
+        if (*end) {
+            if (end[0] != CR || end[1] != LF || (end[2] != ' ' &&
+                                                 end[2] != '\t')) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
+                              "Response header '%s' value of '%s' contains "
+                              "invalid characters, aborting request",
+                              name, pos);
+                return 0;
+            }
+            if (!dst) {
+                *val = dst = apr_palloc(ctx->r->pool, strlen(*val) + 1);
+            }
+        }
+        if (dst) {
+            memcpy(dst, pos, end - pos);
+            dst += end - pos;
+            if (*end) {
+                /* skip folding and replace with a single space */
+                end += 3 + strspn(end + 3, "\t ");
+                *dst++ = ' ';
+            }
+        }
+    }
+    if (dst) {
+        *dst = '\0';
+    }
+    return 1;
+}
+
+static int check_headers_table(apr_table_t *t, struct check_header_ctx *ctx)
+{
+    const apr_array_header_t *headers = apr_table_elts(t);
+    apr_table_entry_t *header;
+    int i;
+
+    for (i = 0; i < headers->nelts; ++i) {
+        header = &((apr_table_entry_t *)headers->elts)[i];
+        if (!header->key) {
+            continue;
+        }
+        if (!check_header(ctx, header->key, (const char **)&header->val)) {
+            return 0;
+        }
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
+        (core_server_config *)ap_get_module_config(r->server->module_config,
+                                                   &core_module);
+
+    ctx.r = r;
+    ctx.strict = (conf->http_conformance != AP_HTTP_CONFORMANCE_UNSAFE);
+    return check_headers_table(r->headers_out, &ctx) &&
+           check_headers_table(r->err_headers_out, &ctx);
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
