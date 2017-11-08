static const char *h2_protocol_get(const conn_rec *c)
{
    return h2_ctx_protocol_get(c);
}