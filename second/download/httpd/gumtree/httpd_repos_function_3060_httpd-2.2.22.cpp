static apr_status_t crypto_block_decrypt_init(apr_crypto_block_t **ctx,
        apr_size_t *blockSize, const unsigned char *iv,
        const apr_crypto_key_t *key, apr_pool_t *p)
{
    PRErrorCode perr;
    SECItem * secParam;
    apr_crypto_block_t *block = *ctx;
    if (!block) {
        *ctx = block = apr_pcalloc(p, sizeof(apr_crypto_block_t));
    }
    if (!block) {
        return APR_ENOMEM;
    }
    block->f = key->f;
    block->pool = p;
    block->provider = key->provider;

    apr_pool_cleanup_register(p, block, crypto_block_cleanup_helper,
            apr_pool_cleanup_null);

    if (key->ivSize) {
        SECItem ivItem;
        if (iv == NULL) {
            return APR_ENOIV; /* Cannot initialise without an IV */
        }
        ivItem.data = (unsigned char*) iv;
        ivItem.len = key->ivSize;
        secParam = PK11_ParamFromIV(key->cipherMech, &ivItem);
    }
    else {
        secParam = PK11_GenerateNewParam(key->cipherMech, key->symKey);
    }
    block->blockSize = PK11_GetBlockSize(key->cipherMech, secParam);
    block->ctx = PK11_CreateContextBySymKey(key->cipherMech, CKA_DECRYPT,
            key->symKey, secParam);

    /* did an error occur? */
    perr = PORT_GetError();
    if (perr || !block->ctx) {
        key->f->result->rc = perr;
        key->f->result->msg = PR_ErrorToName(perr);
        return APR_EINIT;
    }

    if (blockSize) {
        *blockSize = PK11_GetBlockSize(key->cipherMech, secParam);
    }

    return APR_SUCCESS;

}