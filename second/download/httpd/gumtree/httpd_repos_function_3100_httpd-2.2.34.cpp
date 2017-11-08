static apr_status_t crypto_block_decrypt_finish(unsigned char *out,
        apr_size_t *outlen, apr_crypto_block_t *block)
{

    apr_status_t rv = APR_SUCCESS;
    unsigned int outl = *outlen;

    SECStatus s = PK11_DigestFinal(block->ctx, out, &outl, block->blockSize);
    *outlen = outl;

    if (s != SECSuccess) {
        PRErrorCode perr = PORT_GetError();
        if (perr) {
            block->f->result->rc = perr;
            block->f->result->msg = PR_ErrorToName(perr);
        }
        rv = APR_ECRYPT;
    }
    crypto_block_cleanup(block);

    return rv;

}