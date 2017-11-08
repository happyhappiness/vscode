void apr__SHA512_Update(SHA512_CTX* context, const sha2_byte *data, size_t len) {
        unsigned int    freespace, usedspace;

        if (len == 0) {
                /* Calling with no data is valid - we do nothing */
                return;
        }

        /* Sanity check: */
        assert(context != (SHA512_CTX*)0 && data != (sha2_byte*)0);

        usedspace = (unsigned int)((context->bitcount[0] >> 3) 
                                 % SHA512_BLOCK_LENGTH);
        if (usedspace > 0) {
                /* Calculate how much free space is available in the buffer */
                freespace = SHA512_BLOCK_LENGTH - usedspace;

                if (len >= freespace) {
                        /* Fill the buffer completely and process it */
                        MEMCPY_BCOPY(&context->buffer[usedspace], data, freespace);
                        ADDINC128(context->bitcount, freespace << 3);
                        len -= freespace;
                        data += freespace;
                        apr__SHA512_Transform(context, (sha2_word64*)context->buffer);
                } else {
                        /* The buffer is not yet full */
                        MEMCPY_BCOPY(&context->buffer[usedspace], data, len);
                        ADDINC128(context->bitcount, len << 3);
                        /* Clean up: */
                        usedspace = freespace = 0;
                        return;
                }
        }
        while (len >= SHA512_BLOCK_LENGTH) {
                /* Process as many complete blocks as we can */
                apr__SHA512_Transform(context, (sha2_word64*)data);
                ADDINC128(context->bitcount, SHA512_BLOCK_LENGTH << 3);
                len -= SHA512_BLOCK_LENGTH;
                data += SHA512_BLOCK_LENGTH;
        }
        if (len > 0) {
                /* There's left-overs, so save 'em */
                MEMCPY_BCOPY(context->buffer, data, len);
                ADDINC128(context->bitcount, len << 3);
        }
        /* Clean up: */
        usedspace = freespace = 0;
}