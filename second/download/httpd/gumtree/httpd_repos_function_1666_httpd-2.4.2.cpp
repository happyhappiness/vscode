static  apr_status_t  hm_update_stat(hm_ctx_t *ctx, hm_server_t *s, apr_pool_t *pool)
{
    if (slotmem)
        return hm_slotmem_update_stat(s, pool);
    else
        return hm_file_update_stat(ctx, s, pool);
}