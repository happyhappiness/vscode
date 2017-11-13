static apr_status_t encrypt_string(request_rec * r, const apr_crypto_t *f,
        session_crypto_dir_conf *dconf, const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_key_t *key = NULL;
    apr_size_t ivSize = 0;
    apr_crypto_block_t *block = NULL;
    unsigned char *encrypt = NULL;
    unsigned char *combined = NULL;
    apr_size_t encryptlen, tlen;
    char *base64;
    apr_size_t blockSize = 0;
    const unsigned char *iv = NULL;
    apr_uuid_t salt;
    apr_crypto_block_key_type_e *cipher;
    const char *passphrase;

    /* by default, return an empty string */
    *out = "";

    /* don't attempt to encrypt an empty string, trying to do so causes a segfault */
    if (!in || !*in) {
        return APR_SUCCESS;
    }

    /* use a uuid as a salt value, and prepend it to our result */
    apr_uuid_get(&salt);
    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* encrypt using the first passphrase in the list */
    passphrase = APR_ARRAY_IDX(dconf->passphrases, 0, char *);
    res = apr_crypto_passphrase(&key, &ivSize, passphrase,
            strlen(passphrase),
            (unsigned char *) (&salt), sizeof(apr_uuid_t),
            *cipher, APR_MODE_CBC, 1, 4096, f, r->pool);
    if (APR_STATUS_IS_ENOKEY(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01825)
                "the passphrase '%s' was empty", passphrase);
    }
    if (APR_STATUS_IS_EPADDING(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01826)
                "padding is not supported for cipher");
    }
    if (APR_STATUS_IS_EKEYTYPE(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01827)
                "the key type is not known");
    }
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01828)
                "encryption could not be configured.");
        return res;
    }

    res = apr_crypto_block_encrypt_init(&block, &iv, key, &blockSize, r->pool);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01829)
                "apr_crypto_block_encrypt_init failed");
        return res;
    }

    /* encrypt the given string */
    res = apr_crypto_block_encrypt(&encrypt, &encryptlen, (unsigned char *)in,
            strlen(in), block);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01830)
                "apr_crypto_block_encrypt failed");
        return res;
    }
    res = apr_crypto_block_encrypt_finish(encrypt + encryptlen, &tlen, block);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01831)
                "apr_crypto_block_encrypt_finish failed");
        return res;
    }
    encryptlen += tlen;

    /* prepend the salt and the iv to the result */
    combined = apr_palloc(r->pool, ivSize + encryptlen + sizeof(apr_uuid_t));
    memcpy(combined, &salt, sizeof(apr_uuid_t));
    memcpy(combined + sizeof(apr_uuid_t), iv, ivSize);
    memcpy(combined + sizeof(apr_uuid_t) + ivSize, encrypt, encryptlen);

    /* base64 encode the result */
    base64 = apr_palloc(r->pool, apr_base64_encode_len(ivSize + encryptlen +
                    sizeof(apr_uuid_t) + 1)
            * sizeof(char));
    apr_base64_encode(base64, (const char *) combined,
            ivSize + encryptlen + sizeof(apr_uuid_t));
    *out = base64;

    return res;

}