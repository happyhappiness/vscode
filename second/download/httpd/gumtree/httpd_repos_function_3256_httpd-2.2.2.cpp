void apr__SHA512_Last(SHA512_CTX* context) {
        unsigned int    usedspace;

        usedspace = (unsigned int)((context->bitcount[0] >> 3) 
                                 % SHA512_BLOCK_LENGTH);
#if !APR_IS_BIGENDIAN
        /* Convert FROM host byte order */
        REVERSE64(context->bitcount[0],context->bitcount[0]);
        REVERSE64(context->bitcount[1],context->bitcount[1]);
#endif
        if (usedspace > 0) {
                /* Begin padding with a 1 bit: */
                context->buffer[usedspace++] = 0x80;

                if (usedspace <= SHA512_SHORT_BLOCK_LENGTH) {
                        /* Set-up for the last transform: */
                        MEMSET_BZERO(&context->buffer[usedspace], SHA512_SHORT_BLOCK_LENGTH - usedspace);
                } else {
                        if (usedspace < SHA512_BLOCK_LENGTH) {
                                MEMSET_BZERO(&context->buffer[usedspace], SHA512_BLOCK_LENGTH - usedspace);
                        }
                        /* Do second-to-last transform: */
                        apr__SHA512_Transform(context, (sha2_word64*)context->buffer);

                        /* And set-up for the last transform: */
                        MEMSET_BZERO(context->buffer, SHA512_BLOCK_LENGTH - 2);
                }
        } else {
                /* Prepare for final transform: */
                MEMSET_BZERO(context->buffer, SHA512_SHORT_BLOCK_LENGTH);

                /* Begin padding with a 1 bit: */
                *context->buffer = 0x80;
        }
        /* Store the length of input data (in bits): */
        *(sha2_word64*)&context->buffer[SHA512_SHORT_BLOCK_LENGTH] = context->bitcount[1];
        *(sha2_word64*)&context->buffer[SHA512_SHORT_BLOCK_LENGTH+8] = context->bitcount[0];

        /* Final transform: */
        apr__SHA512_Transform(context, (sha2_word64*)context->buffer);
}