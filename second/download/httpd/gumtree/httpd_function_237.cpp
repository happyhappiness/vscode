static apr_status_t ssl_io_filter_cleanup(void *data)
{
    apr_status_t ret;
    ssl_filter_ctx_t *filter_ctx = (ssl_filter_ctx_t *)data;
    conn_rec *c;

    if (!filter_ctx->pssl) {
        /* already been shutdown */
        return APR_SUCCESS;
    }

    c = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    if ((ret = ssl_filter_io_shutdown(filter_ctx, c, 0)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_INFO, ret, NULL,
                     "SSL filter error shutting down I/O");
    }

    return ret;
}