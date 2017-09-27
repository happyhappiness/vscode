                      * found in the cache, eject it in favor of the completed obj.
                      */
                     cache_object_t *tmp_obj =
                       (cache_object_t *) cache_find(sconf->cache_cache, obj->key);
                     if (tmp_obj) {
                         cache_remove(sconf->cache_cache, tmp_obj);
-                        sconf->object_cnt--;
-                        sconf->cache_size -= mobj->m_len;
                         tmp_obj->cleanup = 1;
                         if (!tmp_obj->refcount) {
                             cleanup_cache_object(tmp_obj);
                         }
                     }
                     obj->cleanup = 0;
                 }
                 else {
                     cache_remove(sconf->cache_cache, obj);
                 }
                 mobj->m_len = obj->count;
                 cache_insert(sconf->cache_cache, obj);                
-                sconf->cache_size -= (mobj->m_len - obj->count);
                 if (sconf->lock) {
                     apr_thread_mutex_unlock(sconf->lock);
                 }
             }
             /* Open for business */
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
