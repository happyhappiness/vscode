static apr_status_t modssl_ctx_config_cleanup(void *ctx)
{
    SSL_CONF_CTX_free(ctx);
    return APR_SUCCESS;
}