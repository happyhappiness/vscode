static apr_status_t hm_update_stats(hm_ctx_t *ctx, apr_pool_t *p)
{
    if (slotmem)
        return hm_slotmem_update_stats(ctx, p);
    else
        return hm_file_update_stats(ctx, p);
}