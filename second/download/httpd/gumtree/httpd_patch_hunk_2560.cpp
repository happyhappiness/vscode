     if (ctx && ctx->shm) {
         apr_shm_destroy(ctx->shm);
         ctx->shm = NULL;
     }
 }
 
-static apr_status_t socache_shmcb_store(ap_socache_instance_t *ctx, 
-                                        server_rec *s, const unsigned char *id, 
-                                        unsigned int idlen, apr_time_t expiry, 
+static apr_status_t socache_shmcb_store(ap_socache_instance_t *ctx,
+                                        server_rec *s, const unsigned char *id,
+                                        unsigned int idlen, apr_time_t expiry,
                                         unsigned char *encoded,
                                         unsigned int len_encoded,
                                         apr_pool_t *p)
 {
     SHMCBHeader *header = ctx->header;
     SHMCBSubcache *subcache = SHMCB_MASK(header, id);
     int tryreplace;
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00831)
                  "socache_shmcb_store (0x%02x -> subcache %d)",
                  SHMCB_MASK_DBG(header, id));
     /* XXX: Says who?  Why shouldn't this be acceptable, or padded if not? */
     if (idlen < 4) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short id provided "
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00832) "unusably short id provided "
                 "(%u bytes)", idlen);
         return APR_EINVAL;
     }
     tryreplace = shmcb_subcache_remove(s, header, subcache, id, idlen);
     if (shmcb_subcache_store(s, header, subcache, encoded,
                              len_encoded, id, idlen, expiry)) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00833)
                      "can't store an socache entry!");
         return APR_ENOSPC;
     }
     if (tryreplace == 0) {
         header->stat_replaced++;
     }
     else {
         header->stat_stores++;
     }
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00834)
                  "leaving socache_shmcb_store successfully");
     return APR_SUCCESS;
 }
 
-static apr_status_t socache_shmcb_retrieve(ap_socache_instance_t *ctx, 
-                                           server_rec *s, 
+static apr_status_t socache_shmcb_retrieve(ap_socache_instance_t *ctx,
+                                           server_rec *s,
                                            const unsigned char *id, unsigned int idlen,
                                            unsigned char *dest, unsigned int *destlen,
                                            apr_pool_t *p)
 {
     SHMCBHeader *header = ctx->header;
     SHMCBSubcache *subcache = SHMCB_MASK(header, id);
     int rv;
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00835)
                  "socache_shmcb_retrieve (0x%02x -> subcache %d)",
                  SHMCB_MASK_DBG(header, id));
 
     /* Get the entry corresponding to the id, if it exists. */
     rv = shmcb_subcache_retrieve(s, header, subcache, id, idlen,
                                  dest, destlen);
     if (rv == 0)
         header->stat_retrieves_hit++;
     else
         header->stat_retrieves_miss++;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00836)
                  "leaving socache_shmcb_retrieve successfully");
 
     return rv == 0 ? APR_SUCCESS : APR_NOTFOUND;
 }
 
-static apr_status_t socache_shmcb_remove(ap_socache_instance_t *ctx, 
+static apr_status_t socache_shmcb_remove(ap_socache_instance_t *ctx,
                                          server_rec *s, const unsigned char *id,
                                          unsigned int idlen, apr_pool_t *p)
 {
     SHMCBHeader *header = ctx->header;
     SHMCBSubcache *subcache = SHMCB_MASK(header, id);
     apr_status_t rv;
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00837)
                  "socache_shmcb_remove (0x%02x -> subcache %d)",
                  SHMCB_MASK_DBG(header, id));
     if (idlen < 4) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short id provided "
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00838) "unusably short id provided "
                 "(%u bytes)", idlen);
         return APR_EINVAL;
     }
     if (shmcb_subcache_remove(s, header, subcache, id, idlen) == 0) {
         header->stat_removes_hit++;
         rv = APR_SUCCESS;
     } else {
         header->stat_removes_miss++;
         rv = APR_NOTFOUND;
     }
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00839)
                  "leaving socache_shmcb_remove successfully");
 
     return rv;
 }
 
-static void socache_shmcb_status(ap_socache_instance_t *ctx, 
+static void socache_shmcb_status(ap_socache_instance_t *ctx,
                                  request_rec *r, int flags)
 {
     server_rec *s = r->server;
     SHMCBHeader *header = ctx->header;
     unsigned int loop, total = 0, cache_total = 0, non_empty_subcaches = 0;
-    apr_time_t idx_expiry, min_expiry = 0, max_expiry = 0, average_expiry = 0;
+    apr_time_t idx_expiry, min_expiry = 0, max_expiry = 0;
     apr_time_t now = apr_time_now();
     double expiry_total = 0;
     int index_pct, cache_pct;
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "inside shmcb_status");
+    AP_DEBUG_ASSERT(header->subcache_num > 0);
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00840) "inside shmcb_status");
     /* Perform the iteration inside the mutex to avoid corruption or invalid
      * pointer arithmetic. The rest of our logic uses read-only header data so
      * doesn't need the lock. */
     /* Iterate over the subcaches */
     for (loop = 0; loop < header->subcache_num; loop++) {
         SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
