                 * to remove the object, update the size and re-add the 
                 * object, all under protection of the lock.
                 */
                if (sconf->lock) {
                    apr_thread_mutex_lock(sconf->lock);
                }
                /* Has the object been ejected from the cache?
                 */
                tobj = (cache_object_t *) cache_find(sconf->cache_cache, obj->key);
                if (tobj == obj) {
                    /* Object is still in the cache, remove it, update the len field then
                     * replace it under protection of sconf->lock.
                     */
                    cache_remove(sconf->cache_cache, obj);
                    /* For illustration, cache no longer has reference to the object
                     * so decrement the refcount
                     * apr_atomic_dec(&obj->refcount); 
                     */
                    mobj->m_len = obj->count;

                    cache_insert(sconf->cache_cache, obj);
                    /* For illustration, cache now has reference to the object, so
                     * increment the refcount
                     * apr_atomic_inc(&obj->refcount); 
                     */
                }
                else if (tobj) {
                    /* Different object with the same key found in the cache. Doing nothing
                     * here will cause the object refcount to drop to 0 in decrement_refcount
                     * and the object will be cleaned up.
                     */

                } else {
                    /* Object has been ejected from the cache, add it back to the cache */
                    mobj->m_len = obj->count;
                    cache_insert(sconf->cache_cache, obj);
                    apr_atomic_inc(&obj->refcount); 
                }

                if (sconf->lock) {
                    apr_thread_mutex_unlock(sconf->lock);
                }
            }
            /* Open for business */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
