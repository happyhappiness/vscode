static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb) 
{
    apr_bucket *b;
    mem_cache_object_t *mobj = (mem_cache_object_t*) h->cache_obj->vobj;

    if (mobj->type == CACHE_TYPE_FILE) {
        /* CACHE_TYPE_FILE */
        apr_file_t *file;
        apr_os_file_put(&file, &mobj->fd, mobj->flags, p);
        b = apr_bucket_file_create(file, 0, mobj->m_len, p, bb->bucket_alloc);
    }
    else {
        /* CACHE_TYPE_HEAP */
        b = apr_bucket_immortal_create(mobj->m, mobj->m_len, bb->bucket_alloc);
    }
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_eos_create(bb->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    return APR_SUCCESS;
}