void apr__SHA384_Init(SHA384_CTX* context) {
        if (context == (SHA384_CTX*)0) {
                return;
        }
        MEMCPY_BCOPY(context->state, sha384_initial_hash_value, SHA512_DIGEST_LENGTH);
        MEMSET_BZERO(context->buffer, SHA384_BLOCK_LENGTH);
        context->bitcount[0] = context->bitcount[1] = 0;
}