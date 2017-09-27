          * Note: a new response that has an older Date header value than
          * existing cached responses is not cacheable.
          */
         reason = "updated entity is older than cached entity";
 
         /* while this response is not cacheable, the previous response still is */
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00770)
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02474)
                 "cache: Removing CACHE_REMOVE_URL filter.");
         ap_remove_output_filter(cache->remove_url_filter);
     }
     else if (r->status == HTTP_NOT_MODIFIED && cache->stale_handle) {
         apr_table_t *left = cache->stale_handle->resp_hdrs;
         apr_table_t *right = r->headers_out;
