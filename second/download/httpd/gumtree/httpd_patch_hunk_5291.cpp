                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01111)
                                   "readbytes: %#x", readbytes);
                     }
 #endif
                     /* sanity check */
                     if (APR_BRIGADE_EMPTY(bb)) {
-                        apr_brigade_cleanup(bb);
                         break;
                     }
 
                     /* Switch the allocator lifetime of the buckets */
                     proxy_buckets_lifetime_transform(r, bb, pass_bb);
 
