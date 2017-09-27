     idx->expires = expiry;
     idx->data_pos = id_offset;
     idx->data_used = total_len;
     idx->id_len = id_len;
     idx->removed = 0;
     subcache->idx_used++;
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "insert happened at idx=%d, data=(%u:%u)", new_idx, 
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00847)
+                 "insert happened at idx=%d, data=(%u:%u)", new_idx,
                  id_offset, data_offset);
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00848)
                  "finished insert, subcache: idx_pos/idx_used=%d/%d, "
                  "data_pos/data_used=%d/%d",
                  subcache->idx_pos, subcache->idx_used,
                  subcache->data_pos, subcache->data_used);
     return 0;
 }
 
 static int shmcb_subcache_retrieve(server_rec *s, SHMCBHeader *header,
-                                   SHMCBSubcache *subcache, 
+                                   SHMCBSubcache *subcache,
                                    const unsigned char *id, unsigned int idlen,
                                    unsigned char *dest, unsigned int *destlen)
 {
     unsigned int pos;
     unsigned int loop = 0;
     apr_time_t now = apr_time_now();
