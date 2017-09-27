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
