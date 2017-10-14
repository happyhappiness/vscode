static void hc_send(sctx_t *ctx, apr_pool_t *ptemp, const char *out, proxy_conn_rec *backend)
{
    apr_bucket_brigade *tmp_bb = apr_brigade_create(ptemp, ctx->ba);
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, ctx->s, "%s", out);
    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_pool_create(out, strlen(out), ptemp,
                            ctx->ba));
    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_flush_create(ctx->ba));
    ap_pass_brigade(backend->connection->output_filters, tmp_bb);
    apr_brigade_destroy(tmp_bb);
}