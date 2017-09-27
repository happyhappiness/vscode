     if (!h2_util_ignore_header(key)) {
         (*((size_t*)ctx))++;
     }
     return 1;
 }
 
-#define NV_ADD_LIT_CS(nv, k, v)     add_header(nv, k, sizeof(k) - 1, v, strlen(v))
-#define NV_ADD_CS_CS(nv, k, v)      add_header(nv, k, strlen(k), v, strlen(v))
+static const char *inv_field_name_chr(const char *token)
+{
+    const char *p = ap_scan_http_token(token);
+    if (p == token && *p == ':') {
+        p = ap_scan_http_token(++p);
+    }
+    return (p && *p)? p : NULL;
+}
 
-static int add_header(h2_ngheader *ngh, 
-                      const char *key, size_t key_len,
-                      const char *value, size_t val_len)
+static const char *inv_field_value_chr(const char *token)
 {
-    nghttp2_nv *nv = &ngh->nv[ngh->nvlen++];
-    
+    const char *p = ap_scan_http_field_content(token);
+    return (p && *p)? p : NULL;
+}
+
+typedef struct ngh_ctx {
+    apr_pool_t *p;
+    int unsafe;
+    h2_ngheader *ngh;
+    apr_status_t status;
+} ngh_ctx;
+
+static int add_header(ngh_ctx *ctx, const char *key, const char *value)
+{
+    nghttp2_nv *nv = &(ctx->ngh)->nv[(ctx->ngh)->nvlen++];
+    const char *p;
+
+    if (!ctx->unsafe) {
+        if ((p = inv_field_name_chr(key))) {
+            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
+                          "h2_request: head field '%s: %s' has invalid char %s", 
+                          key, value, p);
+            ctx->status = APR_EINVAL;
+            return 0;
+        }
+        if ((p = inv_field_value_chr(value))) {
+            ap_log_perror(APLOG_MARK, APLOG_TRACE1, APR_EINVAL, ctx->p,
+                          "h2_request: head field '%s: %s' has invalid char %s", 
+                          key, value, p);
+            ctx->status = APR_EINVAL;
+            return 0;
+        }
+    }
     nv->name = (uint8_t*)key;
-    nv->namelen = key_len;
+    nv->namelen = strlen(key);
     nv->value = (uint8_t*)value;
-    nv->valuelen = val_len;
+    nv->valuelen = strlen(value);
+    
     return 1;
 }
 
 static int add_table_header(void *ctx, const char *key, const char *value)
 {
     if (!h2_util_ignore_header(key)) {
-        add_header(ctx, key, strlen(key), value, strlen(value));
+        add_header(ctx, key, value);
     }
     return 1;
 }
 
-
-h2_ngheader *h2_util_ngheader_make(apr_pool_t *p, apr_table_t *header)
+static apr_status_t ngheader_create(h2_ngheader **ph, apr_pool_t *p, 
+                                    int unsafe, size_t key_count, 
+                                    const char *keys[], const char *values[],
+                                    apr_table_t *headers)
 {
-    h2_ngheader *ngh;
-    size_t n;
+    ngh_ctx ctx;
+    size_t n, i;
+    
+    ctx.p = p;
+    ctx.unsafe = unsafe;
+    
+    n = key_count;
+    apr_table_do(count_header, &n, headers, NULL);
+    
+    *ph = ctx.ngh = apr_pcalloc(p, sizeof(h2_ngheader));
+    if (!ctx.ngh) {
+        return APR_ENOMEM;
+    }
+    
+    ctx.ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
+    if (!ctx.ngh->nv) {
+        return APR_ENOMEM;
+    }
     
-    n = 0;
-    apr_table_do(count_header, &n, header, NULL);
+    ctx.status = APR_SUCCESS;
+    for (i = 0; i < key_count; ++i) {
+        if (!add_header(&ctx, keys[i], values[i])) {
+            return ctx.status;
+        }
+    }
     
-    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
-    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
-    apr_table_do(add_table_header, ngh, header, NULL);
+    apr_table_do(add_table_header, &ctx, headers, NULL);
 
-    return ngh;
+    return ctx.status;
 }
 
-h2_ngheader *h2_util_ngheader_make_res(apr_pool_t *p, 
-                                       int http_status, 
-                                       apr_table_t *header)
+static int is_unsafe(h2_headers *h)
 {
-    h2_ngheader *ngh;
-    size_t n;
-    
-    n = 1;
-    apr_table_do(count_header, &n, header, NULL);
-    
-    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
-    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
-    NV_ADD_LIT_CS(ngh, ":status", apr_psprintf(p, "%d", http_status));
-    apr_table_do(add_table_header, ngh, header, NULL);
+    const char *v = apr_table_get(h->notes, H2_HDR_CONFORMANCE);
+    return (v && !strcmp(v, H2_HDR_CONFORMANCE_UNSAFE));
+}
 
-    return ngh;
+apr_status_t h2_res_create_ngtrailer(h2_ngheader **ph, apr_pool_t *p, 
+                                    h2_headers *headers)
+{
+    return ngheader_create(ph, p, is_unsafe(headers), 
+                           0, NULL, NULL, headers->headers);
+}
+                                     
+apr_status_t h2_res_create_ngheader(h2_ngheader **ph, apr_pool_t *p,
+                                    h2_headers *headers) 
+{
+    const char *keys[] = {
+        ":status"
+    };
+    const char *values[] = {
+        apr_psprintf(p, "%d", headers->status)
+    };
+    return ngheader_create(ph, p, is_unsafe(headers),  
+                           H2_ALEN(keys), keys, values, headers->headers);
 }
 
-h2_ngheader *h2_util_ngheader_make_req(apr_pool_t *p, 
-                                       const struct h2_request *req)
+apr_status_t h2_req_create_ngheader(h2_ngheader **ph, apr_pool_t *p, 
+                                    const struct h2_request *req)
 {
     
-    h2_ngheader *ngh;
-    size_t n;
+    const char *keys[] = {
+        ":scheme", 
+        ":authority", 
+        ":path", 
+        ":method", 
+    };
+    const char *values[] = {
+        req->scheme,
+        req->authority, 
+        req->path, 
+        req->method, 
+    };
     
-    ap_assert(req);
     ap_assert(req->scheme);
     ap_assert(req->authority);
     ap_assert(req->path);
     ap_assert(req->method);
 
-    n = 4;
-    apr_table_do(count_header, &n, req->headers, NULL);
-    
-    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
-    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
-    NV_ADD_LIT_CS(ngh, ":scheme", req->scheme);
-    NV_ADD_LIT_CS(ngh, ":authority", req->authority);
-    NV_ADD_LIT_CS(ngh, ":path", req->path);
-    NV_ADD_LIT_CS(ngh, ":method", req->method);
-    apr_table_do(add_table_header, ngh, req->headers, NULL);
-
-    return ngh;
+    return ngheader_create(ph, p, 0, H2_ALEN(keys), keys, values, req->headers);
 }
 
 /*******************************************************************************
  * header HTTP/1 <-> HTTP/2 conversions
  ******************************************************************************/
  
