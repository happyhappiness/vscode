char *SHA512_End(SHA512_CTX* context, char buffer[]) {
        sha2_byte       digest[SHA512_DIGEST_LENGTH], *d = digest;
        int             i;

        /* Sanity check: */
        assert(context != (SHA512_CTX*)0);

        if (buffer != (char*)0) {
                SHA512_Final(digest, context);

                for (i = 0; i < SHA512_DIGEST_LENGTH; i++) {
                        *buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
                        *buffer++ = sha2_hex_digits[*d & 0x0f];
                        d++;
                }
                *buffer = (char)0;
        } else {
                MEMSET_BZERO(context, sizeof(context));
        }
        MEMSET_BZERO(digest, SHA512_DIGEST_LENGTH);
        return buffer;
}