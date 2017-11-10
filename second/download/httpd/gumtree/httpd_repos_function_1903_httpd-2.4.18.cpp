static  apr_status_t  hm_slotmem_remove_stat(hm_server_t *s, apr_pool_t *pool)
{
    hm_slot_server_ctx_t ctx;
    ctx.s = s;
    ctx.found = 0;
    storage->doall(slotmem, hm_readid, &ctx, pool);
    if (ctx.found) {
        storage->release(slotmem, ctx.item_id);
    }
    return APR_SUCCESS;
}