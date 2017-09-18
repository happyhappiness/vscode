    cache_object_t *obj = h->cache_obj;

    /* Remove the cache object from the cache under protection */
    if (sconf->lock) {
        apr_thread_mutex_lock(sconf->lock);
    }
    /* Set the cleanup flag. Object will be cleaned up (by decrement_refcount)
     * when the refcount drops to zero.
     */
    obj->cleanup = 1;
    obj = (cache_object_t *) apr_hash_get(sconf->cacheht, obj->key,
                                          APR_HASH_KEY_STRING);
    if (obj && obj->complete) {
        mem_cache_object_t *mobj = (mem_cache_object_t *) obj->vobj;
        apr_hash_set(sconf->cacheht, obj->key, strlen(obj->key), NULL);
        sconf->object_cnt--;
        sconf->cache_size -= mobj->m_len;
    }
    if (sconf->lock) {
        apr_thread_mutex_unlock(sconf->lock);
    }

    h->cache_obj = NULL;
    return OK;
}
static apr_status_t serialize_table(cache_header_tbl_t **obj, 
                                    apr_ssize_t *nelts, 
                                    apr_table_t *table)
{
