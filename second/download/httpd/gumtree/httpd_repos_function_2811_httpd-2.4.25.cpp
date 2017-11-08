h2_ctx *h2_ctx_rget(const request_rec *r)
{
    return h2_ctx_get(r->connection, 0);
}