static apr_status_t stat_cache_cleanup(void *data)
{
    apr_pool_t *p = (apr_pool_t *)getGlobalPool();
    apr_hash_index_t *hi;
    apr_hash_t *statCache = (apr_hash_t*)data;
	char *key;
    apr_ssize_t keylen;
    NXPathCtx_t pathctx;

    for (hi = apr_hash_first(p, statCache); hi; hi = apr_hash_next(hi)) {
        apr_hash_this(hi, (const void**)&key, &keylen, (void**)&pathctx);

        if (pathctx) {
            NXFreePathContext(pathctx);
        }
    }

    return APR_SUCCESS;
}