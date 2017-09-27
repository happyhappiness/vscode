      * unix domain sockets) because overhead is negligable and it reduces the
      * performance/stability danger of file-descriptor bloatage. */
 #define SESSION_CTX_FLAGS        0
 #endif
     ctx->dc = DC_CTX_new(ctx->target, SESSION_CTX_FLAGS);
     if (!ctx->dc) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache failed to obtain context");
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00738) "distributed scache failed to obtain context");
         return APR_EGENERAL;
     }
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, "distributed scache context initialised");
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(00739) "distributed scache context initialised");
 
     return APR_SUCCESS;
 }
 
 static void socache_dc_destroy(ap_socache_instance_t *ctx, server_rec *s)
 {
     if (ctx && ctx->dc) {
         DC_CTX_free(ctx->dc);
         ctx->dc = NULL;
     }
 }
 
-static apr_status_t socache_dc_store(ap_socache_instance_t *ctx, server_rec *s, 
+static apr_status_t socache_dc_store(ap_socache_instance_t *ctx, server_rec *s,
                                      const unsigned char *id, unsigned int idlen,
-                                     time_t expiry,
+                                     apr_time_t expiry,
                                      unsigned char *der, unsigned int der_len,
                                      apr_pool_t *p)
 {
-    /* !@#$%^ - why do we deal with *absolute* time anyway??? 
+    /* !@#$%^ - why do we deal with *absolute* time anyway???
      * Uhm - because most things expire things at a specific time?
      * Were the API were thought out expiry - r->request_time is a good approximation
      */
-    expiry -= apr_time_t(NULL);
+    expiry -= apr_time_now();
     /* Send the serialised session to the distributed cache context */
     if (!DC_CTX_add_session(ctx->dc, id, idlen, der, der_len,
-                            apr_time_in_msec(expiry)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'store' failed");
+                            apr_time_msec(expiry))) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00740) "distributed scache 'store' failed");
         return APR_EGENERAL;
     }
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'store' successful");
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00741) "distributed scache 'store' successful");
     return APR_SUCCESS;
 }
 
-static apr_status_t socache_dc_retrieve(ap_socache_instance_t *ctx, server_rec *s, 
+static apr_status_t socache_dc_retrieve(ap_socache_instance_t *ctx, server_rec *s,
                                         const unsigned char *id, unsigned int idlen,
                                         unsigned char *dest, unsigned int *destlen,
                                         apr_pool_t *p)
 {
     unsigned int data_len;
 
     /* Retrieve any corresponding session from the distributed cache context */
     if (!DC_CTX_get_session(ctx->dc, id, idlen, dest, *destlen, &data_len)) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'retrieve' MISS");
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00742) "distributed scache 'retrieve' MISS");
         return APR_NOTFOUND;
     }
     if (data_len > *destlen) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'retrieve' OVERFLOW");
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00743) "distributed scache 'retrieve' OVERFLOW");
         return APR_ENOSPC;
     }
     *destlen = data_len;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'retrieve' HIT");
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00744) "distributed scache 'retrieve' HIT");
     return APR_SUCCESS;
 }
 
-static apr_status_t socache_dc_remove(ap_socache_instance_t *ctx, 
-                                      server_rec *s, const unsigned char *id, 
+static apr_status_t socache_dc_remove(ap_socache_instance_t *ctx,
+                                      server_rec *s, const unsigned char *id,
                                       unsigned int idlen, apr_pool_t *p)
 {
     /* Remove any corresponding session from the distributed cache context */
     if (!DC_CTX_remove_session(ctx->dc, id, idlen)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove' MISS");
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00745) "distributed scache 'remove' MISS");
         return APR_NOTFOUND;
     } else {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove' HIT");
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00746) "distributed scache 'remove' HIT");
         return APR_SUCCESS;
     }
 }
 
 static void socache_dc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
 {
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00747)
                   "distributed scache 'socache_dc_status'");
     ap_rprintf(r, "cache type: <b>DC (Distributed Cache)</b>, "
                " target: <b>%s</b><br>", ctx->target);
 }
 
 static apr_status_t socache_dc_iterate(ap_socache_instance_t *instance,
