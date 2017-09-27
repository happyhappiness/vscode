                                     (long)(b->length == ((apr_size_t)-1)? 
                                            -1 : b->length));
             }
         }
         line = *buffer? buffer : "(empty)";
     }
+    /* Intentional no APLOGNO */
     ap_log_cerror(APLOG_MARK, level, 0, c, "bb_dump(%ld-%d)-%s: %s", 
                   c->id, stream_id, tag, line);
 
 }
 
-apr_status_t h2_transfer_brigade(apr_bucket_brigade *to,
+apr_status_t h2_ltransfer_brigade(apr_bucket_brigade *to,
                                  apr_bucket_brigade *from, 
                                  apr_pool_t *p,
                                  apr_off_t *plen,
                                  int *peos)
 {
     apr_bucket *e;
