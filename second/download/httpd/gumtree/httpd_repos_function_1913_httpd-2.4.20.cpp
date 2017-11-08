static hm_server_t *hm_get_server(hm_ctx_t *ctx, const char *ip, const int port)
{
    hm_server_t *s;

    s = apr_hash_get(ctx->servers, ip, APR_HASH_KEY_STRING);

    if (s == NULL) {
        s = apr_palloc(ctx->p, sizeof(hm_server_t));
        s->ip = apr_pstrdup(ctx->p, ip);
        s->port = port;
        s->ready = 0;
        s->busy = 0;
        s->seen = 0;
        apr_hash_set(ctx->servers, s->ip, APR_HASH_KEY_STRING, s);
    }

    return s;
}