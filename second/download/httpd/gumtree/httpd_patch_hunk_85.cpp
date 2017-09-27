     /* Iterate accross the brigade and populate the cache storage */
     APR_BRIGADE_FOREACH(e, b) {
         const char *s;
         apr_size_t len;
 
         if (APR_BUCKET_IS_EOS(e)) {
+            if (mobj->m_len > obj->count) {
+                /* Caching a streamed response. Reallocate a buffer of the 
+                 * correct size and copy the streamed response into that 
+                 * buffer */
+                char *buf = malloc(obj->count);
+                if (!buf) {
+                    return APR_ENOMEM;
+                }
+                memcpy(buf, mobj->m, obj->count);
+                free(mobj->m);
+                mobj->m = buf;
+
+                /* Now comes the crufty part... there is no way to tell the
+                 * cache that the size of the object has changed. We need
+                 * to remove the object, update the size and re-add the 
+                 * object, all under protection of the lock.
+                 */
+                if (sconf->lock) {
+                    apr_thread_mutex_lock(sconf->lock);
+                }
+                cache_remove(sconf->cache_cache, obj);
+                mobj->m_len = obj->count;
+                cache_insert(sconf->cache_cache, obj);                
+                sconf->cache_size -= (mobj->m_len - obj->count);
+                if (sconf->lock) {
+                    apr_thread_mutex_unlock(sconf->lock);
+                }
+            }
             /* Open for business */
+            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
+                         "mem_cache: Cached url: %s", obj->key);
             obj->complete = 1;
             break;
         }
         rv = apr_bucket_read(e, &s, &len, eblock);
         if (rv != APR_SUCCESS) {
             return rv;
