static apr_status_t crypto_cleanup(apr_crypto_t *f)
{

    if (f->config->engine) {
        ENGINE_finish(f->config->engine);
        ENGINE_free(f->config->engine);
        f->config->engine = NULL;
    }
    return APR_SUCCESS;

}