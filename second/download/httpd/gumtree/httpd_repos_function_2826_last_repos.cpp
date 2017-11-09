apr_status_t h2_session_rcreate(h2_session **psession, 
                                request_rec *r, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(psession, r->connection, r, ctx, workers);
}