static apr_status_t write_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b) 
{
    apr_status_t rv;
    cache_object_t *obj = h->cache_obj;
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
        APR_BRIGADE_FOREACH(e, b) {
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
            rv = apr_file_open(&tmpfile, name, 
                               APR_READ | APR_BINARY | APR_XTHREAD | APR_FILE_NOCLEANUP,
                               APR_OS_DEFAULT, r->pool);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            apr_file_unset_inherit(tmpfile);
            apr_os_file_get(&(mobj->fd), tmpfile);

            /* Open for business */
            obj->complete = 1;
            return APR_SUCCESS;
        }

        /* Content not suitable for fd caching. Cache in-memory instead. */
        mobj->type = CACHE_TYPE_HEAP;
        /* Check to make sure the object will not exceed configured thresholds */
        if (mobj->m_len < sconf->min_cache_object_size || 
            mobj->m_len > sconf->max_cache_object_size) {
            return APR_ENOMEM; /* ?? DECLINED; */
        }
        if ((sconf->cache_size + mobj->m_len) > sconf->max_cache_size) {
            return APR_ENOMEM; /* ?? DECLINED; */
        }
        sconf->cache_size += mobj->m_len;
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
    APR_BRIGADE_FOREACH(e, b) {
        const char *s;
        apr_size_t len;

        if (APR_BUCKET_IS_EOS(e)) {
            /* Open for business */
            obj->complete = 1;
            break;
        }
        rv = apr_bucket_read(e, &s, &len, eblock);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len) {
            /* Check for buffer overflow */
           if ((obj->count + len) > mobj->m_len) {
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