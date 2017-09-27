    decoded = apr_palloc(r->pool, apr_base64_decode_len(in));
    decodedlen = apr_base64_decode(decoded, in);
    decoded[decodedlen] = '\0';

    /* sanity check - decoded too short? */
    if (decodedlen < (AP_SIPHASH_DSIZE + sizeof(apr_uuid_t))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(10005)
                "too short to decrypt, aborting");
        return APR_ECRYPT;
    }

    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
