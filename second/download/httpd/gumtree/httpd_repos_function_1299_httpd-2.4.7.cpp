static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p,
        apr_bucket_brigade *bb)
{
    cache_socache_object_t *sobj = (cache_socache_object_t*) h->cache_obj->vobj;
    apr_bucket *e;

    e = APR_BRIGADE_FIRST(sobj->body);

    if (e != APR_BRIGADE_SENTINEL(sobj->body)) {
        APR_BUCKET_REMOVE(e);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }

    return APR_SUCCESS;
}