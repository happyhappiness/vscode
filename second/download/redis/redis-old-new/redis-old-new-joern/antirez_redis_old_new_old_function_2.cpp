RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(void*), long long timeout_ms) {
    client *c = ctx->client;
    c->bpop.module_blocked_handle = zmalloc(sizeof(RedisModuleBlockedClient));
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;

    bc->client = c;
    bc->module = ctx->module;
    bc->reply_callback = reply_callback;
    bc->timeout_callback = timeout_callback;
    bc->free_privdata = free_privdata;
    bc->privdata = NULL;
    bc->reply_client = createClient(-1);
    bc->reply_client->flags |= CLIENT_MODULE;
    bc->dbid = c->db->id;
    c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;

    blockClient(c,BLOCKED_MODULE);
    return bc;
}