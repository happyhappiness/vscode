static apr_status_t crypto_block_encrypt_finish(unsigned char *out,
        apr_size_t *outlen, apr_crypto_block_t *ctx)
{
    int len = *outlen;

    if (EVP_EncryptFinal_ex(&ctx->cipherCtx, out, &len) == 0) {
        return APR_EPADDING;
    }
    *outlen = len;

    return APR_SUCCESS;

}