apr_status_t h2_session_create(h2_session **psession, 
                               conn_rec *c, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(psession, c, NULL, ctx, workers);
}