static apr_status_t crypto_block_decrypt(unsigned char **out,
        apr_size_t *outlen, const unsigned char *in, apr_size_t inlen,
        apr_crypto_block_t *ctx)
{
    int outl = *outlen;
    unsigned char *buffer;

    /* are we after the maximum size of the out buffer? */
    if (!out) {
        *outlen = inlen + EVP_MAX_BLOCK_LENGTH;
        return APR_SUCCESS;
    }

    /* must we allocate the output buffer from a pool? */
    if (!(*out)) {
        buffer = apr_palloc(ctx->pool, inlen + EVP_MAX_BLOCK_LENGTH);
        if (!buffer) {
            return APR_ENOMEM;
        }
        apr_crypto_clear(ctx->pool, buffer, inlen + EVP_MAX_BLOCK_LENGTH);
        *out = buffer;
    }

#if CRYPT_OPENSSL_CONST_BUFFERS
    if (!EVP_DecryptUpdate(&ctx->cipherCtx, *out, &outl, in, inlen)) {
#else
    if (!EVP_DecryptUpdate(&ctx->cipherCtx, *out, &outl, (unsigned char *) in,
            inlen)) {
#endif
        return APR_ECRYPT;
    }
    *outlen = outl;

    return APR_SUCCESS;

}

/**
 * @brief Decrypt final data block, write it to out.
 * @note If necessary the final block will be written out after being
 *       padded. Typically the final block will be written to the
 *       same buffer used by apr_crypto_block_decrypt, offset by the
 *       number of bytes returned as actually written by the
 *       apr_crypto_block_decrypt() call. After this call, the context
 *       is cleaned and can be reused by apr_crypto_block_decrypt_init().
 * @param out Address of a buffer to which data will be written. This
 *            buffer must already exist, and is usually the same
 *            buffer used by apr_evp_crypt(). See note.
 * @param outlen Length of the output will be written here.
 * @param ctx The block context to use.
 * @return APR_ECRYPT if an error occurred.
 * @return APR_EPADDING if padding was enabled and the block was incorrectly
 *         formatted.
 * @return APR_ENOTIMPL if not implemented.
 */
static apr_status_t crypto_block_decrypt_finish(unsigned char *out,
        apr_size_t *outlen, apr_crypto_block_t *ctx)
{

    int len = *outlen;

    if (EVP_DecryptFinal_ex(&ctx->cipherCtx, out, &len) == 0) {
        return APR_EPADDING;
    }
    *outlen = len;

    return APR_SUCCESS;

}

/**
 * OpenSSL module.
 */
APU_MODULE_DECLARE_DATA const apr_crypto_driver_t apr_crypto_openssl_driver = {
    "openssl", crypto_init, crypto_make, crypto_get_block_key_types,
    crypto_get_block_key_modes, crypto_passphrase,
    crypto_block_encrypt_init, crypto_block_encrypt,
    crypto_block_encrypt_finish, crypto_block_decrypt_init,
    crypto_block_decrypt, crypto_block_decrypt_finish,
    crypto_block_cleanup, crypto_cleanup, crypto_shutdown, crypto_error
};