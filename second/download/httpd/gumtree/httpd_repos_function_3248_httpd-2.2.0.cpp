void SHA512_Init(SHA512_CTX* context) {
        if (context == (SHA512_CTX*)0) {
                return;
        }
        MEMCPY_BCOPY(context->state, sha512_initial_hash_value, SHA512_DIGEST_LENGTH);
        MEMSET_BZERO(context->buffer, SHA512_BLOCK_LENGTH);
        context->bitcount[0] = context->bitcount[1] =  0;
}