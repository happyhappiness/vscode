static void compute_auth(const void *src, apr_size_t len,
                         const char *passphrase, apr_size_t passlen,
                         unsigned char auth[AP_SIPHASH_DSIZE])
{
    unsigned char key[APR_MD5_DIGESTSIZE];

    /* XXX: if we had a way to get the raw bytes from an apr_crypto_key_t
     *      we could use them directly (not available in APR-1.5.x).
     * MD5 is 128bit too, so use it to get a suitable siphash key
     * from the passphrase.
     */
    apr_md5(key, passphrase, passlen);

    ap_siphash24_auth(auth, src, len, key);
}