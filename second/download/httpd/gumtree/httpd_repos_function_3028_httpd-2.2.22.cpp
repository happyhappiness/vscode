static apr_status_t crypto_passphrase(apr_crypto_key_t **k, apr_size_t *ivSize,
        const char *pass, apr_size_t passLen, const unsigned char * salt,
        apr_size_t saltLen, const apr_crypto_block_key_type_e type,
        const apr_crypto_block_key_mode_e mode, const int doPad,
        const int iterations, const apr_crypto_t *f, apr_pool_t *p)
{
    apr_crypto_key_t *key = *k;

    if (!key) {
        *k = key = apr_array_push(f->keys);
    }
    if (!key) {
        return APR_ENOMEM;
    }

    key->f = f;
    key->provider = f->provider;

    /* determine the cipher to be used */
    switch (type) {

    case (APR_KEY_3DES_192):

        /* A 3DES key */
        if (mode == APR_MODE_CBC) {
            key->cipher = EVP_des_ede3_cbc();
        }
        else {
            key->cipher = EVP_des_ede3_ecb();
        }
        break;

    case (APR_KEY_AES_128):

        if (mode == APR_MODE_CBC) {
            key->cipher = EVP_aes_128_cbc();
        }
        else {
            key->cipher = EVP_aes_128_ecb();
        }
        break;

    case (APR_KEY_AES_192):

        if (mode == APR_MODE_CBC) {
            key->cipher = EVP_aes_192_cbc();
        }
        else {
            key->cipher = EVP_aes_192_ecb();
        }
        break;

    case (APR_KEY_AES_256):

        if (mode == APR_MODE_CBC) {
            key->cipher = EVP_aes_256_cbc();
        }
        else {
            key->cipher = EVP_aes_256_ecb();
        }
        break;

    default:

        /* unknown key type, give up */
        return APR_EKEYTYPE;

    }

    /* find the length of the key we need */
    key->keyLen = EVP_CIPHER_key_length(key->cipher);

    /* make space for the key */
    key->key = apr_pcalloc(p, key->keyLen);
    if (!key->key) {
        return APR_ENOMEM;
    }
    apr_crypto_clear(p, key->key, key->keyLen);

    /* generate the key */
    if (PKCS5_PBKDF2_HMAC_SHA1(pass, passLen, (unsigned char *) salt, saltLen,
            iterations, key->keyLen, key->key) == 0) {
        return APR_ENOKEY;
    }

    key->doPad = doPad;

    /* note: openssl incorrectly returns non zero IV size values for ECB
     * algorithms, so work around this by ignoring the IV size.
     */
    if (APR_MODE_ECB != mode) {
        key->ivSize = EVP_CIPHER_iv_length(key->cipher);
    }
    if (ivSize) {
        *ivSize = key->ivSize;
    }

    return APR_SUCCESS;
}