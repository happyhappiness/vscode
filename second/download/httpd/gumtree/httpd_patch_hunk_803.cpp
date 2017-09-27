     }
     else {
         /* Split a line into the passed-in brigade. */
         rv = apr_brigade_split_line(bb, ctx->bb, mode, bytes);
 
         if (rv) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, f->c,
                           "could not split line from buffered SSL brigade");
             ap_remove_input_filter(f);
             return rv;
         }
     }
 
     if (APR_BRIGADE_EMPTY(ctx->bb)) {
         apr_bucket *e = APR_BRIGADE_LAST(bb);
-        
+
         /* Ensure that the brigade is terminated by an EOS if the
          * buffered request body has been entirely consumed. */
         if (e == APR_BRIGADE_SENTINEL(bb) || !APR_BUCKET_IS_EOS(e)) {
             e = apr_bucket_eos_create(f->c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(bb, e);
         }
 
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                       "buffered SSL brigade now exhausted; removing filter");
         ap_remove_input_filter(f);
     }
 
     return APR_SUCCESS;
 }
