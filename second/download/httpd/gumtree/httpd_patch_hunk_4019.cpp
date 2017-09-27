 
 apr_status_t h2_request_add_trailer(h2_request *req, apr_pool_t *pool,
                                     const char *name, size_t nlen,
                                     const char *value, size_t vlen)
 {
     if (!req->trailers) {
-        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool,
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03059)
                       "h2_request(%d): unanounced trailers",
                       req->id);
         return APR_EINVAL;
     }
     if (nlen == 0 || name[0] == ':') {
-        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool,
+        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03060)
                       "h2_request(%d): pseudo header in trailer",
                       req->id);
         return APR_EINVAL;
     }
     return add_h1_trailer(req, pool, name, nlen, value, vlen);
 }
 
 #define OPT_COPY(p, s)  ((s)? apr_pstrdup(p, s) : NULL)
 
 void h2_request_copy(apr_pool_t *p, h2_request *dst, const h2_request *src)
 {
     /* keep the dst id */
+    dst->initiated_on   = src->initiated_on;
     dst->method         = OPT_COPY(p, src->method);
     dst->scheme         = OPT_COPY(p, src->scheme);
     dst->authority      = OPT_COPY(p, src->authority);
     dst->path           = OPT_COPY(p, src->path);
     dst->headers        = apr_table_clone(p, src->headers);
+    if (src->trailers) {
+        dst->trailers   = apr_table_clone(p, src->trailers);
+    }
+    else {
+        dst->trailers   = NULL;
+    }
     dst->content_length = src->content_length;
     dst->chunked        = src->chunked;
     dst->eoh            = src->eoh;
+    dst->body           = src->body;
+    dst->serialize      = src->serialize;
+    dst->push_policy    = src->push_policy;
+}
+
+h2_request *h2_request_clone(apr_pool_t *p, const h2_request *src)
+{
+    h2_request *nreq = apr_pcalloc(p, sizeof(*nreq));
+    memcpy(nreq, src, sizeof(*nreq));
+    h2_request_copy(p, nreq, src);
+    return nreq;
 }
 
 request_rec *h2_request_create_rec(const h2_request *req, conn_rec *conn)
 {
     request_rec *r;
     apr_pool_t *p;
