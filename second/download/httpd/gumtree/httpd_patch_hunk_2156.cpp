         if (e == APR_BRIGADE_SENTINEL(bb) || !APR_BUCKET_IS_EOS(e)) {
             e = apr_bucket_eos_create(f->c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, e);
         }
 
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
-                      "buffered SSL brigade now exhausted; removing filter");
-        ap_remove_input_filter(f);
+                      "buffered SSL brigade exhausted");
+        /* Note that the filter must *not* be removed here; it may be
+         * invoked again, see comment above. */
     }
 
     return APR_SUCCESS;
 }
 
 static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
