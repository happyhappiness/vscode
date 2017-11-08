static void ssl_io_filter_disable(SSLConnRec *sslconn,
                                  bio_filter_in_ctx_t *inctx)
{
    SSL_free(inctx->ssl);
    sslconn->ssl = NULL;
    inctx->ssl = NULL;
    inctx->filter_ctx->pssl = NULL;
}