void apr__SHA256_Final(sha2_byte digest[], SHA256_CTX* context) {
        sha2_word32     *d = (sha2_word32*)digest;
        unsigned int    usedspace;

        /* Sanity check: */
        assert(context != (SHA256_CTX*)0);

        /* If no digest buffer is passed, we don't bother doing this: */
        if (digest != (sha2_byte*)0) {
                usedspace = (unsigned int)((context->bitcount >> 3) 
                                         % SHA256_BLOCK_LENGTH);
#if !APR_IS_BIGENDIAN
                /* Convert FROM host byte order */
                REVERSE64(context->bitcount,context->bitcount);
#endif
                if (usedspace > 0) {
                        /* Begin padding with a 1 bit: */
                        context->buffer[usedspace++] = 0x80;

                        if (usedspace <= SHA256_SHORT_BLOCK_LENGTH) {
                                /* Set-up for the last transform: */
                                MEMSET_BZERO(&context->buffer[usedspace], SHA256_SHORT_BLOCK_LENGTH - usedspace);
                        } else {
                                if (usedspace < SHA256_BLOCK_LENGTH) {
                                        MEMSET_BZERO(&context->buffer[usedspace], SHA256_BLOCK_LENGTH - usedspace);
                                }
                                /* Do second-to-last transform: */
                                apr__SHA256_Transform(context, (sha2_word32*)context->buffer);

                                /* And set-up for the last transform: */
                                MEMSET_BZERO(context->buffer, SHA256_SHORT_BLOCK_LENGTH);
                        }
                } else {
                        /* Set-up for the last transform: */
                        MEMSET_BZERO(context->buffer, SHA256_SHORT_BLOCK_LENGTH);

                        /* Begin padding with a 1 bit: */
                        *context->buffer = 0x80;
                }
                /* Set the bit count: */
                {
                        union dummy {
                                apr_uint64_t bitcount;
                                apr_byte_t bytes[8];
                        } bitcount;
                        bitcount.bitcount = context->bitcount;
                        MEMCPY_BCOPY(&context->buffer[SHA256_SHORT_BLOCK_LENGTH], bitcount.bytes, 8);
                }

                /* Final transform: */
                apr__SHA256_Transform(context, (sha2_word32*)context->buffer);

#if !APR_IS_BIGENDIAN
                {
                        /* Convert TO host byte order */
                        int     j;
                        for (j = 0; j < 8; j++) {
                                REVERSE32(context->state[j],context->state[j]);
                                *d++ = context->state[j];
                        }
                }
#else
                MEMCPY_BCOPY(d, context->state, SHA256_DIGEST_LENGTH);
#endif
        }

        /* Clean up state data: */
        MEMSET_BZERO(context, sizeof(*context));
        usedspace = 0;
}