{
    const char *keystr = ssl_asn1_keystr(keytype);

    return apr_pstrcat(p, id, ":", keystr, NULL);
}


#if APR_HAS_THREADS
/*
 * To ensure thread-safetyness in OpenSSL - work in progress
 */

