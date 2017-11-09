apr_status_t h2_conn_pre_close(struct h2_ctx *ctx, conn_rec *c)
{
    h2_session *session = h2_ctx_session_get(ctx);
    if (session) {
        apr_status_t status = h2_session_pre_close(session, async_mpm);
        return (status == APR_SUCCESS)? DONE : status;
    }
    return DONE;
}