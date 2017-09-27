static int lua_request_hook(lua_State *L, request_rec *r)
{
    ap_lua_push_request(L, r);
    return OK;
}

static int lua_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    lua_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    lua_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    return OK;
}
static void *overlay_hook_specs(apr_pool_t *p,
                                        const void *key,
                                        apr_ssize_t klen,
                                        const void *overlay_val,
