apr_status_t h2_conn_pre_close(struct h2_ctx *ctx, conn_rec *c)
{
    apr_status_t status;
    
    status = h2_session_pre_close(h2_ctx_session_get(ctx), async_mpm);
    if (status == APR_SUCCESS) {
        return DONE; /* This is the same, right? */
    }
    return status;
}