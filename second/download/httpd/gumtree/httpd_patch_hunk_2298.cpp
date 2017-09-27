                                         unsigned char *encoded,
                                         unsigned int len_encoded,
                                         apr_pool_t *p)
 {
     SHMCBHeader *header = ctx->header;
     SHMCBSubcache *subcache = SHMCB_MASK(header, id);
+    int tryreplace;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "socache_shmcb_store (0x%02x -> subcache %d)",
                  SHMCB_MASK_DBG(header, id));
     /* XXX: Says who?  Why shouldn't this be acceptable, or padded if not? */
     if (idlen < 4) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "unusably short id provided "
                 "(%u bytes)", idlen);
         return APR_EINVAL;
     }
+    tryreplace = shmcb_subcache_remove(s, header, subcache, id, idlen);
     if (shmcb_subcache_store(s, header, subcache, encoded,
                              len_encoded, id, idlen, expiry)) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "can't store an socache entry!");
         return APR_ENOSPC;
     }
-    header->stat_stores++;
+    if (tryreplace == 0) {
+        header->stat_replaced++;
+    }
+    else {
+        header->stat_stores++;
+    }
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "leaving socache_shmcb_store successfully");
     return APR_SUCCESS;
 }
 
 static apr_status_t socache_shmcb_retrieve(ap_socache_instance_t *ctx, 
