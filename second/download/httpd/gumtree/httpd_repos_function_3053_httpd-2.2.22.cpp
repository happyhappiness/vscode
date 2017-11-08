static apr_status_t crypto_make(apr_crypto_t **ff,
        const apr_crypto_driver_t *provider, const char *params,
        apr_pool_t *pool)
{
    apr_crypto_config_t *config = NULL;
    apr_crypto_t *f;

    f = apr_pcalloc(pool, sizeof(apr_crypto_t));
    if (!f) {
        return APR_ENOMEM;
    }
    *ff = f;
    f->pool = pool;
    f->provider = provider;
    config = f->config = apr_pcalloc(pool, sizeof(apr_crypto_config_t));
    if (!config) {
        return APR_ENOMEM;
    }
    f->result = apr_pcalloc(pool, sizeof(apu_err_t));
    if (!f->result) {
        return APR_ENOMEM;
    }
    f->keys = apr_array_make(pool, 10, sizeof(apr_crypto_key_t));

    f->types = apr_hash_make(pool);
    if (!f->types) {
        return APR_ENOMEM;
    }
    apr_hash_set(f->types, "3des192", APR_HASH_KEY_STRING, &(key_3des_192));
    apr_hash_set(f->types, "aes128", APR_HASH_KEY_STRING, &(key_aes_128));
    apr_hash_set(f->types, "aes192", APR_HASH_KEY_STRING, &(key_aes_192));
    apr_hash_set(f->types, "aes256", APR_HASH_KEY_STRING, &(key_aes_256));

    f->modes = apr_hash_make(pool);
    if (!f->modes) {
        return APR_ENOMEM;
    }
    apr_hash_set(f->modes, "ecb", APR_HASH_KEY_STRING, &(mode_ecb));
    apr_hash_set(f->modes, "cbc", APR_HASH_KEY_STRING, &(mode_cbc));

    apr_pool_cleanup_register(pool, f, crypto_cleanup_helper,
            apr_pool_cleanup_null);

    return APR_SUCCESS;

}