static int http2_is_h2(conn_rec *c)
{
    return h2_ctx_get(c->master? c->master : c, 0) != NULL;
}