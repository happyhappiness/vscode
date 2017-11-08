static const char *val_H2_STREAM_ID(apr_pool_t *p, server_rec *s,
                                    conn_rec *c, request_rec *r, h2_ctx *ctx)
{
    const char *cp = val_H2_STREAM_TAG(p, s, c, r, ctx);
    if (cp && (cp = ap_strchr_c(cp, '-'))) {
        return ++cp;
    }
    return NULL;
}