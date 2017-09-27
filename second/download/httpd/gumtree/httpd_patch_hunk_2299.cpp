         header->stat_retrieves_hit++;
     else
         header->stat_retrieves_miss++;
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "leaving socache_shmcb_retrieve successfully");
 
-    return rv == 0 ? APR_SUCCESS : APR_EGENERAL;
+    return rv == 0 ? APR_SUCCESS : APR_NOTFOUND;
 }
 
 static apr_status_t socache_shmcb_remove(ap_socache_instance_t *ctx, 
                                          server_rec *s, const unsigned char *id,
                                          unsigned int idlen, apr_pool_t *p)
 {
