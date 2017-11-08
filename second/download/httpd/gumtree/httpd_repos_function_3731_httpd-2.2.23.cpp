char *apr__SHA384_End(SHA384_CTX* context, char buffer[]) {
        sha2_byte       digest[SHA384_DIGEST_LENGTH], *d = digest;
        int             i;

        /* Sanity check: */
        assert(context != (SHA384_CTX*)0);

        if (buffer != (char*)0) {
                apr__SHA384_Final(digest, context);

                for (i = 0; i < SHA384_DIGEST_LENGTH; i++) {
                        *buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
                        *buffer++ = sha2_hex_digits[*d & 0x0f];
                        d++;
                }
                *buffer = (char)0;
        } else {
                MEMSET_BZERO(context, sizeof(*context));
        }
        MEMSET_BZERO(digest, SHA384_DIGEST_LENGTH);
        return buffer;
}