static apr_status_t crypto_block_decrypt(unsigned char **out,
        apr_size_t *outlen, const unsigned char *in, apr_size_t inlen,
        apr_crypto_block_t *block)
{

    unsigned char *buffer;
    int outl = (int) *outlen;
    SECStatus s;
    if (!out) {
        *outlen = inlen + block->blockSize;
        return APR_SUCCESS;
    }
    if (!*out) {
        buffer = apr_palloc(block->pool, inlen + block->blockSize);
        if (!buffer) {
            return APR_ENOMEM;
        }
        apr_crypto_clear(block->pool, buffer, inlen + block->blockSize);
        *out = buffer;
    }

    s = PK11_CipherOp(block->ctx, *out, &outl, inlen, (unsigned char*) in,
            inlen);
    if (s != SECSuccess) {
        PRErrorCode perr = PORT_GetError();
        if (perr) {
            block->f->result->rc = perr;
            block->f->result->msg = PR_ErrorToName(perr);
        }
        return APR_ECRYPT;
    }
    *outlen = outl;

    return APR_SUCCESS;

}