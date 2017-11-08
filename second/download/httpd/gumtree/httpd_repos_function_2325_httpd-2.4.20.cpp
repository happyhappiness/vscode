static char *http2_var_lookup(apr_pool_t *p, server_rec *s,
                              conn_rec *c, request_rec *r, char *name)
{
    int i;
    /* If the # of vars grow, we need to put definitions in a hash */
    for (i = 0; i < H2_ALEN(H2_VARS); ++i) {
        h2_var_def *vdef = &H2_VARS[i];
        if (!strcmp(vdef->name, name)) {
            h2_ctx *ctx = (r? h2_ctx_rget(r) : 
                           h2_ctx_get(c->master? c->master : c, 0));
            return (char *)vdef->lookup(p, s, c, r, ctx);
        }
    }
    return "";
}