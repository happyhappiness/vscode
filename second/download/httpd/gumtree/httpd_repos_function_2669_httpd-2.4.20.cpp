h2_task *h2_ctx_rget_task(request_rec *r)
{
    return h2_ctx_get_task(h2_ctx_rget(r));
}