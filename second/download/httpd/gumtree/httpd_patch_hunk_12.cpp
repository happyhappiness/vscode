 
             /* if we don't get the content-length, see if we have all the 
              * buckets and use their length to calculate the size 
              */
             apr_bucket *e;
             int all_buckets_here=0;
+            int unresolved_length = 0;
             size=0;
             APR_BRIGADE_FOREACH(e, in) {
                 if (APR_BUCKET_IS_EOS(e)) {
                     all_buckets_here=1;
                     break;
                 }
                 if (APR_BUCKET_IS_FLUSH(e)) {
+                    unresolved_length = 1;
                     continue;
                 }
                 if (e->length < 0) {
                     break;
                 }
                 size += e->length;
             }
 
             if (!all_buckets_here) {
-                size = -1;
+                /* Attempt to set aside a copy of a partial response
+                 * in hopes of caching it once the rest of the response
+                 * is available.  There are special cases in which we
+                 * don't try to set aside the content, though:
+                 *   1. The brigade contains at least one bucket of
+                 *      unknown length, such as a pipe or socket bucket.
+                 *   2. The size of the response exceeds the limit set
+                 *      by the CacheMaxStreamingBuffer  directive.
+                 */
+                if (unresolved_length ||
+                    (cache->saved_size + size >
+                     conf->max_streaming_buffer_size)) {
+
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                                 "cache: not caching streamed response for "
+                                 "%s because length %s", url,
+                                 (unresolved_length ?
+                                  "cannot be determined" :
+                                  "> CacheMaxStreamingBuffer"));
+
+                    if (cache->saved_brigade != NULL) {
+                        apr_brigade_destroy(cache->saved_brigade);
+                        cache->saved_brigade = NULL;
+                        cache->saved_size = 0;
+                    }
+                    ap_remove_output_filter(f);
+                    return ap_pass_brigade(f->next, in);
+                }
+
+                /* Add a copy of the new brigade's buckets to the
+                 * saved brigade.  The reason for the copy is so
+                 * that we can output the new buckets immediately,
+                 * rather than having to buffer up the entire
+                 * response before sending anything.
+                 */
+                if (cache->saved_brigade == NULL) {
+                    cache->saved_brigade =
+                        apr_brigade_create(r->pool,
+                                           r->connection->bucket_alloc);
+                    cache->exp = exp;
+                    cache->lastmod = lastmod;
+                    cache->info = info;
+                }
+                APR_BRIGADE_FOREACH(e, in) {
+                    apr_bucket *copy;
+                    apr_bucket_copy(e, &copy);
+                    APR_BRIGADE_INSERT_TAIL(cache->saved_brigade, copy);
+                }
+                cache->saved_size += size;
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                             "cache: Response length still unknown, setting "
+                             "aside content for url: %s", url);
+
+                return ap_pass_brigade(f->next, in);
+            }
+            else {
+                /* Now that we've seen an EOS, it's appropriate
+                 * to try caching the response.  If any content
+                 * has been copied into cache->saved_brigade in
+                 * previous passes through this filter, the
+                 * content placed in the cache must be the
+                 * concatenation of the saved brigade and the
+                 * current brigade.
+                 */
+                if (cache->saved_brigade != NULL) {
+                    split_point = APR_BRIGADE_FIRST(in);
+                    APR_BRIGADE_CONCAT(cache->saved_brigade, in);
+                    in = cache->saved_brigade;
+                    size += cache->saved_size;
+                }
             }
         }
     }
 
     /* It's safe to cache the response.
      *
