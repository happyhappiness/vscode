void apr__SHA256_Update(SHA256_CTX* context, const sha2_byte *data, size_t len) {
        unsigned int    freespace, usedspace;

        if (len == 0) {
                /* Calling with no data is valid - we do nothing */
                return;
        }

        /* Sanity check: */
        assert(context != (SHA256_CTX*)0 && data != (sha2_byte*)0);

        usedspace = (unsigned int)((context->bitcount >> 3) 
                                 % SHA256_BLOCK_LENGTH);
        if (usedspace > 0) {
                /* Calculate how much free space is available in the buffer */
                freespace = SHA256_BLOCK_LENGTH - usedspace;

                if (len >= freespace) {
                        /* Fill the buffer completely and process it */
                        MEMCPY_BCOPY(&context->buffer[usedspace], data, freespace);
                        context->bitcount += freespace << 3;
                        len -= freespace;
                        data += freespace;
                        apr__SHA256_Transform(context, (sha2_word32*)context->buffer);
                } else {
                        /* The buffer is not yet full */
                        MEMCPY_BCOPY(&context->buffer[usedspace], data, len);
                        context->bitcount += len << 3;
                        /* Clean up: */
                        usedspace = freespace = 0;
                        return;
                }
        }
        while (len >= SHA256_BLOCK_LENGTH) {
                /* Process as many complete blocks as we can */
                apr__SHA256_Transform(context, (sha2_word32*)data);
                context->bitcount += SHA256_BLOCK_LENGTH << 3;
                len -= SHA256_BLOCK_LENGTH;
                data += SHA256_BLOCK_LENGTH;
        }
        if (len > 0) {
                /* There's left-overs, so save 'em */
                MEMCPY_BCOPY(context->buffer, data, len);
                context->bitcount += len << 3;
        }
        /* Clean up: */
        usedspace = freespace = 0;
}