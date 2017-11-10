void apr__SHA256_Init(SHA256_CTX* context) {
        if (context == (SHA256_CTX*)0) {
                return;
        }
        MEMCPY_BCOPY(context->state, sha256_initial_hash_value, SHA256_DIGEST_LENGTH);
        MEMSET_BZERO(context->buffer, SHA256_BLOCK_LENGTH);
        context->bitcount = 0;
}