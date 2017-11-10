h2_task *h2_ctx_cget_task(conn_rec *c)
{
    return h2_ctx_get_task(h2_ctx_get(c, 0));
}