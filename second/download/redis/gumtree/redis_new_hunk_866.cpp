 *
 *     free_privdata:   called in order to free the privata data that is passed
 *                      by RedisModule_UnblockClient() call.
 */
RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(void*), long long timeout_ms) {
    client *c = ctx->client;
    int islua = c->flags & CLIENT_LUA;

    c->bpop.module_blocked_handle = zmalloc(sizeof(RedisModuleBlockedClient));
    RedisModuleBlockedClient *bc = c->bpop.module_blocked_handle;

    /* We need to handle the invalid operation of calling modules blocking
     * commands from Lua. We actually create an already aborted (client set to
     * NULL) blocked client handle, and actually reply to Lua with an error. */
    bc->client = islua ? NULL : c;
    bc->module = ctx->module;
    bc->reply_callback = reply_callback;
    bc->timeout_callback = timeout_callback;
    bc->free_privdata = free_privdata;
    bc->privdata = NULL;
    bc->reply_client = createClient(-1);
    bc->reply_client->flags |= CLIENT_MODULE;
    bc->dbid = c->db->id;
    c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;

    if (islua) {
        c->bpop.module_blocked_handle = NULL;
        addReplyError(c,"Blocking module command called from Lua script");
    } else {
        blockClient(c,BLOCKED_MODULE);
    }
    return bc;
}

/* Unblock a client blocked by `RedisModule_BlockedClient`. This will trigger
 * the reply callbacks to be called in order to reply to the client.
 * The 'privdata' argument will be accessible by the reply callback, so
