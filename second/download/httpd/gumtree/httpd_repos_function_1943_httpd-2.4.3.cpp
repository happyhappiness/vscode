static apr_status_t hm_read(void* mem, void *data, apr_pool_t *pool)
{
    hm_slot_server_t *slotserver = (hm_slot_server_t *) mem;
    ctx_servers_t *ctx = (ctx_servers_t *) data;
    apr_hash_t *servers = (apr_hash_t *) ctx->servers;
    hb_server_t *server = apr_hash_get(servers, slotserver->ip, APR_HASH_KEY_STRING);
    if (server == NULL) {
        server = apr_pcalloc(pool, sizeof(hb_server_t));
        server->ip = apr_pstrdup(pool, slotserver->ip);
        server->seen = -1;

        apr_hash_set(servers, server->ip, APR_HASH_KEY_STRING, server);

    }
    server->busy = slotserver->busy;
    server->ready = slotserver->ready;
    server->seen = apr_time_sec(ctx->now - slotserver->seen);
    server->id = slotserver->id;
    if (server->busy == 0 && server->ready != 0) {
        server->ready = server->ready / 4;
    }
    return APR_SUCCESS;
}