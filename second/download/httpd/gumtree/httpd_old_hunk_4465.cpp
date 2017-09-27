    unsigned char *decrypted = NULL;
    apr_size_t decryptedlen, tlen;
    apr_size_t decodedlen;
    char *decoded;
    apr_size_t blockSize = 0;
    apr_crypto_block_key_type_e *cipher;
    int i = 0;

    /* strip base64 from the string */
    decoded = apr_palloc(r->pool, apr_base64_decode_len(in));
    decodedlen = apr_base64_decode(decoded, in);
    decoded[decodedlen] = '\0';

    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* try each passphrase in turn */
    for (; i < dconf->passphrases->nelts; i++) {
        const char *passphrase = APR_ARRAY_IDX(dconf->passphrases, i, char *);
        apr_size_t len = decodedlen;
        char *slider = decoded;

        /* encrypt using the first passphrase in the list */
        res = apr_crypto_passphrase(&key, &ivSize, passphrase,
                strlen(passphrase),
                (unsigned char *)decoded, sizeof(apr_uuid_t),
                *cipher, APR_MODE_CBC, 1, 4096, f, r->pool);
        if (APR_STATUS_IS_ENOKEY(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01832)
                    "the passphrase '%s' was empty", passphrase);
            continue;
        }
        else if (APR_STATUS_IS_EPADDING(res)) {
