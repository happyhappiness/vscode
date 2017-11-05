static apr_status_t decrypt_string(request_rec * r, const apr_crypto_t *f,
        session_crypto_dir_conf *dconf, const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_key_t *key = NULL;
    apr_size_t ivSize = 0;
    apr_crypto_block_t *block = NULL;
    unsigned char *decrypted = NULL;
    apr_size_t decryptedlen, tlen;
    apr_size_t decodedlen;
    char *decoded;
    apr_size_t blockSize = 0;
    apr_crypto_block_key_type_e *cipher;
    unsigned char auth[AP_SIPHASH_DSIZE];
    int i = 0;

    /* strip base64 from the string */
    decoded = apr_palloc(r->pool, apr_base64_decode_len(in));
    decodedlen = apr_base64_decode(decoded, in);
    decoded[decodedlen] = '\0';

    /* sanity check - decoded too short? */
    if (decodedlen < (AP_SIPHASH_DSIZE + sizeof(apr_uuid_t))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO()
                "too short to decrypt, aborting");
        return APR_ECRYPT;
    }

    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* try each passphrase in turn */
    for (; i < dconf->passphrases->nelts; i++) {
        const char *passphrase = APR_ARRAY_IDX(dconf->passphrases, i, char *);
        apr_size_t passlen = strlen(passphrase);
        apr_size_t len = decodedlen - AP_SIPHASH_DSIZE;
        unsigned char *slider = (unsigned char *)decoded + AP_SIPHASH_DSIZE;

        /* Verify authentication of the whole salt+IV+ciphertext by computing
         * the MAC and comparing it (timing safe) with the one in the payload.
         */
        compute_auth(slider, len, passphrase, passlen, auth);
        if (!ap_crypto_equals(auth, decoded, AP_SIPHASH_DSIZE)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO()
                    "auth does not match, skipping");
            continue;
        }

        /* encrypt using the first passphrase in the list */
        res = apr_crypto_passphrase(&key, &ivSize, passphrase, passlen,
                                    slider, sizeof(apr_uuid_t),
                                    *cipher, APR_MODE_CBC, 1, 4096,
                                    f, r->pool);
        if (APR_STATUS_IS_ENOKEY(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01832)
                    "the passphrase '%s' was empty", passphrase);
            continue;
        }
        else if (APR_STATUS_IS_EPADDING(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01833)
                    "padding is not supported for cipher");
            continue;
        }
        else if (APR_STATUS_IS_EKEYTYPE(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01834)
                    "the key type is not known");
            continue;
        }
        else if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01835)
                    "encryption could not be configured.");
            continue;
        }

        /* sanity check - decoded too short? */
        if (len < (sizeof(apr_uuid_t) + ivSize)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(01836)
                    "too short to decrypt, skipping");
            res = APR_ECRYPT;
            continue;
        }

        /* bypass the salt at the start of the decoded block */
        slider += sizeof(apr_uuid_t);
        len -= sizeof(apr_uuid_t);

        res = apr_crypto_block_decrypt_init(&block, &blockSize, slider, key,
                                            r->pool);
        if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01837)
                    "apr_crypto_block_decrypt_init failed");
            continue;
        }

        /* bypass the iv at the start of the decoded block */
        slider += ivSize;
        len -= ivSize;

        /* decrypt the given string */
        res = apr_crypto_block_decrypt(&decrypted, &decryptedlen,
                                       slider, len, block);
        if (res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01838)
                    "apr_crypto_block_decrypt failed");
            continue;
        }
        *out = (char *) decrypted;

        res = apr_crypto_block_decrypt_finish(decrypted + decryptedlen, &tlen, block);
        if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01839)
                    "apr_crypto_block_decrypt_finish failed");
            continue;
        }
        decryptedlen += tlen;
        decrypted[decryptedlen] = 0;

        break;
    }

    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, res, r, APLOGNO(01840)
                "decryption failed");
    }

    return res;

}