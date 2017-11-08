static apr_status_t crypto_block_cleanup(apr_crypto_block_t *block)
{

    if (block->ctx) {
        PK11_DestroyContext(block->ctx, PR_TRUE);
        block->ctx = NULL;
    }

    return APR_SUCCESS;

}