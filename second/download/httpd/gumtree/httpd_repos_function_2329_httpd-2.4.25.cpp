static const char *val_HTTP2(apr_pool_t *p, server_rec *s,
                             conn_rec *c, request_rec *r, h2_ctx *ctx)
{
    return ctx? "on" : "off";
}