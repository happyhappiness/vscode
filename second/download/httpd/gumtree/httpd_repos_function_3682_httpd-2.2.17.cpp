void apr__SHA384_Final(sha2_byte digest[], SHA384_CTX* context) {
        sha2_word64     *d = (sha2_word64*)digest;

        /* Sanity check: */
        assert(context != (SHA384_CTX*)0);

        /* If no digest buffer is passed, we don't bother doing this: */
        if (digest != (sha2_byte*)0) {
                apr__SHA512_Last((SHA512_CTX*)context);

                /* Save the hash data for output: */
#if !APR_IS_BIGENDIAN
                {
                        /* Convert TO host byte order */
                        int     j;
                        for (j = 0; j < 6; j++) {
                                REVERSE64(context->state[j],context->state[j]);
                                *d++ = context->state[j];
                        }
                }
#else /* APR_IS_BIGENDIAN */
                MEMCPY_BCOPY(d, context->state, SHA384_DIGEST_LENGTH);
#endif /* APR_IS_BIGENDIAN */
        }

        /* Zero out state data */
        MEMSET_BZERO(context, sizeof(context));
}