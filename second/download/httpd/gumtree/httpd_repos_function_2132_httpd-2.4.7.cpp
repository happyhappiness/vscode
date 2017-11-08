static apr_status_t readslot_heartbeats(ctx_servers_t *ctx,
                                    apr_pool_t *pool)
{
    storage->doall(hm_serversmem, hm_read, ctx, pool);
    return APR_SUCCESS;
}