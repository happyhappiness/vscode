static apr_status_t crypto_block_cleanup(apr_crypto_block_t *ctx)
{

    if (ctx->initialised) {
        EVP_CIPHER_CTX_cleanup(&ctx->cipherCtx);
        ctx->initialised = 0;
    }

    return APR_SUCCESS;

}