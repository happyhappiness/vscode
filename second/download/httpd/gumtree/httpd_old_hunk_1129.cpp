 * ap_hook_process_connection hook.
 */
static int ssl_io_filter_connect(ssl_filter_ctx_t *filter_ctx)
{
    conn_rec *c         = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    X509 *cert;
    int n;
    int ssl_err;
    long verify_result;

    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    if (sslconn->is_proxy) {
        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return HTTP_BAD_GATEWAY;
        }

        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);
