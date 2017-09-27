                     /* sanity check */
                     if (APR_BRIGADE_EMPTY(bb)) {
                         apr_brigade_cleanup(bb);
                         break;
                     }
 
+                    /* Switch the allocator lifetime of the buckets */
+                    ap_proxy_buckets_lifetime_transform(r, bb, pass_bb);
+
                     /* found the last brigade? */
                     if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
                         /* signal that we must leave */
                         finish = TRUE;
                     }
 
                     /* try send what we read */
-                    if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS
+                    if (ap_pass_brigade(r->output_filters, pass_bb) != APR_SUCCESS
                         || c->aborted) {
                         /* Ack! Phbtt! Die! User aborted! */
                         backend->close = 1;  /* this causes socket close below */
                         finish = TRUE;
                     }
 
                     /* make sure we always clean up after ourselves */
                     apr_brigade_cleanup(bb);
+                    apr_brigade_cleanup(pass_bb);
 
                 } while (!finish);
             }
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: end body send");
         }
