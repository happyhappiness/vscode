         return ap_pass_brigade(f->next, bb);
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                  "cache: running CACHE_OUT filter");
 
-    /* recall_body() was called in cache_select_url() */
+    /* recall_headers() was called in cache_select_url() */
     cache->provider->recall_body(cache->handle, r->pool, bb);
 
     /* This filter is done once it has served up its content */
     ap_remove_output_filter(f);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r->server,
                  "cache: serving %s", r->uri);
     return ap_pass_brigade(f->next, bb);
 }
 
 
 /*
- * CACHE_CONDITIONAL filter
- * ------------------------
- *
- * Decide whether or not cached content should be delivered
- * based on our fudged conditional request.
- * If response HTTP_NOT_MODIFIED
- *   replace ourselves with cache_out filter
- * Otherwise
- *   replace ourselves with cache_save filter
- */
-
-static int cache_conditional_filter(ap_filter_t *f, apr_bucket_brigade *in)
-{
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
-                 "cache: running CACHE_CONDITIONAL filter");
-
-    if (f->r->status == HTTP_NOT_MODIFIED) {
-        /* replace ourselves with CACHE_OUT filter */
-        ap_add_output_filter_handle(cache_out_filter_handle, NULL,
-                                    f->r, f->r->connection);
-    }
-    else {
-        /* replace ourselves with CACHE_SAVE filter */
-        ap_add_output_filter_handle(cache_save_filter_handle, NULL,
-                                    f->r, f->r->connection);
-    }
-    ap_remove_output_filter(f);
-
-    return ap_pass_brigade(f->next, in);
-}
-
-
-/*
  * CACHE_SAVE filter
  * ---------------
  *
  * Decide whether or not this content should be cached.
- * If we decide no it should:
+ * If we decide no it should not:
  *   remove the filter from the chain
  * If we decide yes it should:
- *   pass the data to the storage manager
- *   pass the data to the next filter (the network)
- *
+ *   Have we already started saving the response?
+ *      If we have started, pass the data to the storage manager via store_body
+ *      Otherwise:
+ *        Check to see if we *can* save this particular response.
+ *        If we can, call cache_create_entity() and save the headers and body
+ *   Finally, pass the data to the next filter (the network or whatever)
  */
 
 static int cache_save_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     int rv;
     int date_in_errhdr = 0;
