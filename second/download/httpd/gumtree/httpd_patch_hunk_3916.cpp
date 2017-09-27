     if (status == APR_SUCCESS && !*peos && !*plen) {
         return APR_EAGAIN;
     }
     return status;
 }
 
+void h2_util_bb_log(conn_rec *c, int stream_id, int level, 
+                    const char *tag, apr_bucket_brigade *bb)
+{
+    char buffer[16 * 1024];
+    const char *line = "(null)";
+    apr_size_t bmax = sizeof(buffer)/sizeof(buffer[0]);
+    int off = 0;
+    apr_bucket *b;
+    
+    if (bb) {
+        memset(buffer, 0, bmax--);
+        for (b = APR_BRIGADE_FIRST(bb); 
+             bmax && (b != APR_BRIGADE_SENTINEL(bb));
+             b = APR_BUCKET_NEXT(b)) {
+            
+            if (APR_BUCKET_IS_METADATA(b)) {
+                if (APR_BUCKET_IS_EOS(b)) {
+                    off += apr_snprintf(buffer+off, bmax-off, "eos ");
+                }
+                else if (APR_BUCKET_IS_FLUSH(b)) {
+                    off += apr_snprintf(buffer+off, bmax-off, "flush ");
+                }
+                else if (AP_BUCKET_IS_EOR(b)) {
+                    off += apr_snprintf(buffer+off, bmax-off, "eor ");
+                }
+                else {
+                    off += apr_snprintf(buffer+off, bmax-off, "meta(unknown) ");
+                }
+            }
+            else {
+                const char *btype = "data";
+                if (APR_BUCKET_IS_FILE(b)) {
+                    btype = "file";
+                }
+                else if (APR_BUCKET_IS_PIPE(b)) {
+                    btype = "pipe";
+                }
+                else if (APR_BUCKET_IS_SOCKET(b)) {
+                    btype = "socket";
+                }
+                else if (APR_BUCKET_IS_HEAP(b)) {
+                    btype = "heap";
+                }
+                else if (APR_BUCKET_IS_TRANSIENT(b)) {
+                    btype = "transient";
+                }
+                else if (APR_BUCKET_IS_IMMORTAL(b)) {
+                    btype = "immortal";
+                }
+#if APR_HAS_MMAP
+                else if (APR_BUCKET_IS_MMAP(b)) {
+                    btype = "mmap";
+                }
+#endif
+                else if (APR_BUCKET_IS_POOL(b)) {
+                    btype = "pool";
+                }
+                
+                off += apr_snprintf(buffer+off, bmax-off, "%s[%ld] ", 
+                                    btype, 
+                                    (long)(b->length == ((apr_size_t)-1)? 
+                                           -1 : b->length));
+            }
+        }
+        line = *buffer? buffer : "(empty)";
+    }
+    ap_log_cerror(APLOG_MARK, level, 0, c, "bb_dump(%ld-%d)-%s: %s", 
+                  c->id, stream_id, tag, line);
+
+}
+
+apr_status_t h2_transfer_brigade(apr_bucket_brigade *to,
+                                 apr_bucket_brigade *from, 
+                                 apr_pool_t *p,
+                                 apr_off_t *plen,
+                                 int *peos)
+{
+    apr_bucket *e;
+    apr_off_t len = 0, remain = *plen;
+    apr_status_t rv;
+
+    *peos = 0;
+    
+    while (!APR_BRIGADE_EMPTY(from)) {
+        e = APR_BRIGADE_FIRST(from);
+        
+        if (APR_BUCKET_IS_METADATA(e)) {
+            if (APR_BUCKET_IS_EOS(e)) {
+                *peos = 1;
+            }
+        }
+        else {        
+            if (remain > 0 && e->length == ((apr_size_t)-1)) {
+                const char *ign;
+                apr_size_t ilen;
+                rv = apr_bucket_read(e, &ign, &ilen, APR_BLOCK_READ);
+                if (rv != APR_SUCCESS) {
+                    return rv;
+                }
+            }
+            
+            if (remain < e->length) {
+                if (remain <= 0) {
+                    return APR_SUCCESS;
+                }
+                apr_bucket_split(e, remain);
+            }
+        }
+        
+        rv = apr_bucket_setaside(e, p);
+        
+        /* If the bucket type does not implement setaside, then
+         * (hopefully) morph it into a bucket type which does, and set
+         * *that* aside... */
+        if (rv == APR_ENOTIMPL) {
+            const char *s;
+            apr_size_t n;
+            
+            rv = apr_bucket_read(e, &s, &n, APR_BLOCK_READ);
+            if (rv == APR_SUCCESS) {
+                rv = apr_bucket_setaside(e, p);
+            }
+        }
+        
+        if (rv != APR_SUCCESS) {
+            /* Return an error but still save the brigade if
+             * ->setaside() is really not implemented. */
+            if (rv != APR_ENOTIMPL) {
+                return rv;
+            }
+        }
+        
+        APR_BUCKET_REMOVE(e);
+        APR_BRIGADE_INSERT_TAIL(to, e);
+        len += e->length;
+        remain -= e->length;
+    }
+    
+    *plen = len;
+    return APR_SUCCESS;
+}
+
+/*******************************************************************************
+ * h2_ngheader
+ ******************************************************************************/
+ 
+int h2_util_ignore_header(const char *name) 
+{
+    /* never forward, ch. 8.1.2.2 */
+    return (H2_HD_MATCH_LIT_CS("connection", name)
+            || H2_HD_MATCH_LIT_CS("proxy-connection", name)
+            || H2_HD_MATCH_LIT_CS("upgrade", name)
+            || H2_HD_MATCH_LIT_CS("keep-alive", name)
+            || H2_HD_MATCH_LIT_CS("transfer-encoding", name));
+}
+
+static int count_header(void *ctx, const char *key, const char *value)
+{
+    if (!h2_util_ignore_header(key)) {
+        (*((size_t*)ctx))++;
+    }
+    return 1;
+}
+
+#define NV_ADD_LIT_CS(nv, k, v)     add_header(nv, k, sizeof(k) - 1, v, strlen(v))
+#define NV_ADD_CS_CS(nv, k, v)      add_header(nv, k, strlen(k), v, strlen(v))
+
+static int add_header(h2_ngheader *ngh, 
+                      const char *key, size_t key_len,
+                      const char *value, size_t val_len)
+{
+    nghttp2_nv *nv = &ngh->nv[ngh->nvlen++];
+    
+    nv->name = (uint8_t*)key;
+    nv->namelen = key_len;
+    nv->value = (uint8_t*)value;
+    nv->valuelen = val_len;
+    return 1;
+}
+
+static int add_table_header(void *ctx, const char *key, const char *value)
+{
+    if (!h2_util_ignore_header(key)) {
+        add_header(ctx, key, strlen(key), value, strlen(value));
+    }
+    return 1;
+}
+
+
+h2_ngheader *h2_util_ngheader_make(apr_pool_t *p, apr_table_t *header)
+{
+    h2_ngheader *ngh;
+    size_t n;
+    
+    n = 0;
+    apr_table_do(count_header, &n, header, NULL);
+    
+    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
+    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
+    apr_table_do(add_table_header, ngh, header, NULL);
+
+    return ngh;
+}
+
+h2_ngheader *h2_util_ngheader_make_res(apr_pool_t *p, 
+                                       int http_status, 
+                                       apr_table_t *header)
+{
+    h2_ngheader *ngh;
+    size_t n;
+    
+    n = 1;
+    apr_table_do(count_header, &n, header, NULL);
+    
+    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
+    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
+    NV_ADD_LIT_CS(ngh, ":status", apr_psprintf(p, "%d", http_status));
+    apr_table_do(add_table_header, ngh, header, NULL);
+
+    return ngh;
+}
+
+h2_ngheader *h2_util_ngheader_make_req(apr_pool_t *p, 
+                                       const struct h2_request *req)
+{
+    
+    h2_ngheader *ngh;
+    size_t n;
+    
+    AP_DEBUG_ASSERT(req);
+    AP_DEBUG_ASSERT(req->scheme);
+    AP_DEBUG_ASSERT(req->authority);
+    AP_DEBUG_ASSERT(req->path);
+    AP_DEBUG_ASSERT(req->method);
+
+    n = 4;
+    apr_table_do(count_header, &n, req->headers, NULL);
+    
+    ngh = apr_pcalloc(p, sizeof(h2_ngheader));
+    ngh->nv =  apr_pcalloc(p, n * sizeof(nghttp2_nv));
+    NV_ADD_LIT_CS(ngh, ":scheme", req->scheme);
+    NV_ADD_LIT_CS(ngh, ":authority", req->authority);
+    NV_ADD_LIT_CS(ngh, ":path", req->path);
+    NV_ADD_LIT_CS(ngh, ":method", req->method);
+    apr_table_do(add_table_header, ngh, req->headers, NULL);
+
+    return ngh;
+}
+
+/*******************************************************************************
+ * header HTTP/1 <-> HTTP/2 conversions
+ ******************************************************************************/
+ 
+
+typedef struct {
+    const char *name;
+    size_t len;
+} literal;
+
+#define H2_DEF_LITERAL(n)   { (n), (sizeof(n)-1) }
+#define H2_ALEN(a)          (sizeof(a)/sizeof((a)[0]))
+#define H2_LIT_ARGS(a)      (a),H2_ALEN(a)
+
+static literal IgnoredRequestHeaders[] = {
+    H2_DEF_LITERAL("host"),
+    H2_DEF_LITERAL("expect"),
+    H2_DEF_LITERAL("upgrade"),
+    H2_DEF_LITERAL("connection"),
+    H2_DEF_LITERAL("keep-alive"),
+    H2_DEF_LITERAL("http2-settings"),
+    H2_DEF_LITERAL("proxy-connection"),
+    H2_DEF_LITERAL("transfer-encoding"),
+};
+static literal IgnoredRequestTrailers[] = { /* Ignore, see rfc7230, ch. 4.1.2 */
+    H2_DEF_LITERAL("te"),
+    H2_DEF_LITERAL("host"),
+    H2_DEF_LITERAL("range"),
+    H2_DEF_LITERAL("cookie"),
+    H2_DEF_LITERAL("expect"),
+    H2_DEF_LITERAL("pragma"),
+    H2_DEF_LITERAL("max-forwards"),
+    H2_DEF_LITERAL("cache-control"),
+    H2_DEF_LITERAL("authorization"),
+    H2_DEF_LITERAL("content-length"),       
+    H2_DEF_LITERAL("proxy-authorization"),
+};    
+static literal IgnoredResponseTrailers[] = {
+    H2_DEF_LITERAL("age"),
+    H2_DEF_LITERAL("date"),
+    H2_DEF_LITERAL("vary"),
+    H2_DEF_LITERAL("cookie"),
+    H2_DEF_LITERAL("expires"),
+    H2_DEF_LITERAL("warning"),
+    H2_DEF_LITERAL("location"),
+    H2_DEF_LITERAL("retry-after"),
+    H2_DEF_LITERAL("cache-control"),
+    H2_DEF_LITERAL("www-authenticate"),
+    H2_DEF_LITERAL("proxy-authenticate"),
+};
+
+static int ignore_header(const literal *lits, size_t llen,
+                         const char *name, size_t nlen)
+{
+    const literal *lit;
+    int i;
+    
+    for (i = 0; i < llen; ++i) {
+        lit = &lits[i];
+        if (lit->len == nlen && !apr_strnatcasecmp(lit->name, name)) {
+            return 1;
+        }
+    }
+    return 0;
+}
+
+int h2_req_ignore_header(const char *name, size_t len)
+{
+    return ignore_header(H2_LIT_ARGS(IgnoredRequestHeaders), name, len);
+}
+
+int h2_req_ignore_trailer(const char *name, size_t len)
+{
+    return (h2_req_ignore_header(name, len) 
+            || ignore_header(H2_LIT_ARGS(IgnoredRequestTrailers), name, len));
+}
+
+int h2_res_ignore_trailer(const char *name, size_t len)
+{
+    return ignore_header(H2_LIT_ARGS(IgnoredResponseTrailers), name, len);
+}
+
+void h2_req_strip_ignored_header(apr_table_t *headers)
+{
+    int i;
+    for (i = 0; i < H2_ALEN(IgnoredRequestHeaders); ++i) {
+        apr_table_unset(headers, IgnoredRequestHeaders[i].name);
+    }
+}
+
+
