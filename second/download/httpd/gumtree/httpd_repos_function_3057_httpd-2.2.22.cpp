static apr_status_t crypto_block_encrypt_init(apr_crypto_block_t **ctx,
        const unsigned char **iv, const apr_crypto_key_t *key,
        apr_size_t *blockSize, apr_pool_t *p)
{
    PRErrorCode perr;
    SECItem * secParam;
    SECItem ivItem;
    unsigned char * usedIv;
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
        if (iv == NULL) {
            return APR_ENOIV;
        }
        if (*iv == NULL) {
            SECStatus s;
            usedIv = apr_pcalloc(p, key->ivSize);
            if (!usedIv) {
                return APR_ENOMEM;
            }
            apr_crypto_clear(p, usedIv, key->ivSize);
            s = PK11_GenerateRandom(usedIv, key->ivSize);
            if (s != SECSuccess) {
                return APR_ENOIV;
            }
            *iv = usedIv;
        }
        else {
            usedIv = (unsigned char *) *iv;
        }
        ivItem.data = usedIv;
        ivItem.len = key->ivSize;
        secParam = PK11_ParamFromIV(key->cipherMech, &ivItem);
    }
    else {
        secParam = PK11_GenerateNewParam(key->cipherMech, key->symKey);
    }
    block->blockSize = PK11_GetBlockSize(key->cipherMech, secParam);
    block->ctx = PK11_CreateContextBySymKey(key->cipherMech, CKA_ENCRYPT,
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