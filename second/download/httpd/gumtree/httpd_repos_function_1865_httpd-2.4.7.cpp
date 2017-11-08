static apr_status_t hm_slotmem_update_stats(hm_ctx_t *ctx, apr_pool_t *p)
{
    apr_status_t rv;
    apr_time_t now;
    apr_hash_index_t *hi;
    now = apr_time_now();
    for (hi = apr_hash_first(p, ctx->servers);
         hi != NULL; hi = apr_hash_next(hi)) {
        hm_server_t *s = NULL;
        apr_time_t seen;
        apr_hash_this(hi, NULL, NULL, (void **) &s);
        seen = apr_time_sec(now - s->seen);
        if (seen > SEEN_TIMEOUT) {
            /* remove it */
            rv = hm_slotmem_remove_stat(s, p);
        } else {
            /* update it */
            rv = hm_slotmem_update_stat(s, p);
        }
        if (rv !=APR_SUCCESS)
            return rv;
    }
    return APR_SUCCESS;
}