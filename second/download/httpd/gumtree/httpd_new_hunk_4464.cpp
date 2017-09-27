        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01831)
                "apr_crypto_block_encrypt_finish failed");
        return res;
    }
    encryptlen += tlen;

    /* prepend the salt and the iv to the result (keep room for the MAC) */
    combinedlen = AP_SIPHASH_DSIZE + sizeof(apr_uuid_t) + ivSize + encryptlen;
    combined = apr_palloc(r->pool, combinedlen);
    memcpy(combined + AP_SIPHASH_DSIZE, &salt, sizeof(apr_uuid_t));
    memcpy(combined + AP_SIPHASH_DSIZE + sizeof(apr_uuid_t), iv, ivSize);
    memcpy(combined + AP_SIPHASH_DSIZE + sizeof(apr_uuid_t) + ivSize,
           encrypt, encryptlen);
    /* authenticate the whole salt+IV+ciphertext with a leading MAC */
    compute_auth(combined + AP_SIPHASH_DSIZE, combinedlen - AP_SIPHASH_DSIZE,
                 passphrase, passlen, combined);

    /* base64 encode the result (APR handles the trailing '\0') */
    base64 = apr_palloc(r->pool, apr_base64_encode_len(combinedlen));
    apr_base64_encode(base64, (const char *) combined, combinedlen);
    *out = base64;

    return res;

}

