static  apr_status_t  hm_slotmem_update_stat(hm_server_t *s, apr_pool_t *pool)
{
    /* We call do_all (to try to update) otherwise grab + put */
    hm_slot_server_ctx_t ctx;
    ctx.s = s;
    ctx.found = 0;
    storage->doall(slotmem, hm_update, &ctx, pool);
    if (!ctx.found) {
        unsigned int i;
        hm_slot_server_t hmserver;
        memcpy(hmserver.ip, s->ip, MAXIPSIZE);
        hmserver.busy = s->busy;
        hmserver.ready = s->ready;
        hmserver.seen = s->seen;
        /* XXX locking for grab() / put() */
        storage->grab(slotmem, &i);
        hmserver.id = i;
        storage->put(slotmem, i, (unsigned char *)&hmserver, sizeof(hmserver));
    }
    return APR_SUCCESS;
}