static apr_status_t crypt_init(request_rec *r,
        const apr_crypto_t *f, apr_crypto_block_key_type_e **cipher,
        session_crypto_dir_conf * dconf)
{
    apr_status_t res;
    apr_hash_t *ciphers;

    res = apr_crypto_get_block_key_types(&ciphers, f);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01823)
                "no ciphers returned by APR. "
                "session encryption not possible");
        return res;
    }

    *cipher = apr_hash_get(ciphers, dconf->cipher, APR_HASH_KEY_STRING);
    if (!(*cipher)) {
        apr_hash_index_t *hi;
        const void *key;
        apr_ssize_t klen;
        int sum = 0;
        int offset = 0;
        char *options = NULL;

        for (hi = apr_hash_first(r->pool, ciphers); hi; hi = apr_hash_next(hi)) {
            apr_hash_this(hi, NULL, &klen, NULL);
            sum += klen + 2;
        }
        for (hi = apr_hash_first(r->pool, ciphers); hi; hi = apr_hash_next(hi)) {
            apr_hash_this(hi, &key, &klen, NULL);
            if (!options) {
                options = apr_palloc(r->pool, sum + 1);
            }
            else {
                options[offset++] = ',';
                options[offset++] = ' ';
            }
            strncpy(options + offset, key, klen);
            offset += klen;
        }
        options[offset] = 0;

        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01824)
                "cipher '%s' not recognised by crypto driver. "
                "session encryption not possible, options: %s", dconf->cipher, options);

        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}