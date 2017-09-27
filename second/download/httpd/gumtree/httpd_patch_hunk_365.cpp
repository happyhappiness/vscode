  *
  * Decide whether or not cached content should be delivered
  * based on our fudged conditional request.
  * If response HTTP_NOT_MODIFIED
  *   replace ourselves with cache_out filter
  * Otherwise
- *   replace ourselves with cache_in filter
+ *   replace ourselves with cache_save filter
  */
 
 static int cache_conditional_filter(ap_filter_t *f, apr_bucket_brigade *in)
 {
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
                  "cache: running CACHE_CONDITIONAL filter");
