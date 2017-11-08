static apr_status_t crypto_make(apr_crypto_t **ff,
        const apr_crypto_driver_t *provider, const char *params,
        apr_pool_t *pool)
{
    apr_crypto_config_t *config = NULL;
    apr_crypto_t *f = apr_pcalloc(pool, sizeof(apr_crypto_t));

    const char *engine = NULL;

    struct {
        const char *field;
        const char *value;
        int set;
    } fields[] = {
        { "engine", NULL, 0 },
        { NULL, NULL, 0 }
    };
    const char *ptr;
    size_t klen;
    char **elts = NULL;
    char *elt;
    int i = 0, j;
    apr_status_t status;

    if (params) {
        if (APR_SUCCESS != (status = apr_tokenize_to_argv(params, &elts, pool))) {
            return status;
        }
        while ((elt = elts[i])) {
            ptr = strchr(elt, '=');
            if (ptr) {
                for (klen = ptr - elt; klen && apr_isspace(elt[klen - 1]); --klen)
                    ;
                ptr++;
            }
            else {
                for (klen = strlen(elt); klen && apr_isspace(elt[klen - 1]); --klen)
                    ;
            }
            elt[klen] = 0;

            for (j = 0; fields[j].field != NULL; ++j) {
                if (!strcasecmp(fields[j].field, elt)) {
                    fields[j].set = 1;
                    if (ptr) {
                        fields[j].value = ptr;
                    }
                    break;
                }
            }

            i++;
        }
        engine = fields[0].value;
    }

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
    if (!f->keys) {
        return APR_ENOMEM;
    }

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

    if (engine) {
        config->engine = ENGINE_by_id(engine);
        if (!config->engine) {
            return APR_ENOENGINE;
        }
        if (!ENGINE_init(config->engine)) {
            ENGINE_free(config->engine);
            config->engine = NULL;
            return APR_EINITENGINE;
        }
    }

    return APR_SUCCESS;

}