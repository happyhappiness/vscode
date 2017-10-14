static apr_status_t store_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b)
{
    apr_status_t rv;
    cache_object_t *obj = h->cache_obj;
    cache_object_t *tobj = NULL;
    mem_cache_object_t *mobj = (mem_cache_object_t*) obj->vobj;
    apr_read_type_e eblock = APR_BLOCK_READ;
    apr_bucket *e;
    char *cur;
    int eos = 0;

    if (mobj->type == CACHE_TYPE_FILE) {
        apr_file_t *file = NULL;
        int fd = 0;
        int other = 0;

        /* We can cache an open file descriptor if:
         * - the brigade contains one and only one file_bucket &&
         * - the brigade is complete &&
         * - the file_bucket is the last data bucket in the brigade
         */
        for (e = APR_BRIGADE_FIRST(b);
             e != APR_BRIGADE_SENTINEL(b);
             e = APR_BUCKET_NEXT(e))
        {
            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
            }
            else if (APR_BUCKET_IS_FILE(e)) {
                apr_bucket_file *a = e->data;
                fd++;
                file = a->fd;
            }
            else {
                other++;
            }
        }
        if (fd == 1 && !other && eos) {
            apr_file_t *tmpfile;
            const char *name;
            /* Open a new XTHREAD handle to the file */
            apr_file_name_get(&name, file);
            mobj->flags = ((APR_SENDFILE_ENABLED & apr_file_flags_get(file))
                           | APR_READ | APR_BINARY | APR_XTHREAD | APR_FILE_NOCLEANUP);
            rv = apr_file_open(&tmpfile, name, mobj->flags,
                               APR_OS_DEFAULT, r->pool);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            apr_file_inherit_unset(tmpfile);
            apr_os_file_get(&(mobj->fd), tmpfile);

            /* Open for business */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "mem_cache: Cached file: %s with key: %s", name, obj->key);
            obj->complete = 1;
            return APR_SUCCESS;
        }

        /* Content not suitable for fd caching. Cache in-memory instead. */
        mobj->type = CACHE_TYPE_HEAP;
    }

    /*
     * FD cacheing is not enabled or the content was not
     * suitable for fd caching.
     */
    if (mobj->m == NULL) {
        mobj->m = malloc(mobj->m_len);
        if (mobj->m == NULL) {
            return APR_ENOMEM;
        }
        obj->count = 0;
    }
    cur = (char*) mobj->m + obj->count;

    /* Iterate accross the brigade and populate the cache storage */
    for (e = APR_BRIGADE_FIRST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_NEXT(e))
    {
        const char *s;
        apr_size_t len;

        if (APR_BUCKET_IS_EOS(e)) {
            const char *cl_header = apr_table_get(r->headers_out, "Content-Length");
            if (cl_header) {
                apr_int64_t cl = apr_atoi64(cl_header);
                if ((errno == 0) && (obj->count != cl)) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "mem_cache: URL %s didn't receive complete response, not caching",
                                 h->cache_obj->key);
                    return APR_EGENERAL;
                }
            }
            if (mobj->m_len > obj->count) {
                /* Caching a streamed response. Reallocate a buffer of the
                 * correct size and copy the streamed response into that
                 * buffer */
                mobj->m = realloc(mobj->m, obj->count);
                if (!mobj->m) {
                    return APR_ENOMEM;
                }

                /* Now comes the crufty part... there is no way to tell the
                 * cache that the size of the object has changed. We need
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
                     * apr_atomic_dec32(&obj->refcount);
                     */
                    mobj->m_len = obj->count;

                    cache_insert(sconf->cache_cache, obj);
                    /* For illustration, cache now has reference to the object, so
                     * increment the refcount
                     * apr_atomic_inc32(&obj->refcount);
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
                    apr_atomic_inc32(&obj->refcount);
                }

                if (sconf->lock) {
                    apr_thread_mutex_unlock(sconf->lock);
                }
            }
            /* Open for business */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "mem_cache: Cached url: %s", obj->key);
            obj->complete = 1;
            break;
        }
        rv = apr_bucket_read(e, &s, &len, eblock);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len) {
            /* Check for buffer (max_streaming_buffer_size) overflow  */
           if ((obj->count + len) > mobj->m_len) {
               ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                            "mem_cache: URL %s exceeds the MCacheMaxStreamingBuffer (%" APR_SIZE_T_FMT ") limit and will not be cached.", 
                            obj->key, mobj->m_len);
               return APR_ENOMEM;
           }
           else {
               memcpy(cur, s, len);
               cur+=len;
               obj->count+=len;
           }
        }
        /* This should not fail, but if it does, we are in BIG trouble
         * cause we just stomped all over the heap.
         */
        AP_DEBUG_ASSERT(obj->count <= mobj->m_len);
    }
    return APR_SUCCESS;
}