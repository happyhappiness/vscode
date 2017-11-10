char *apr__SHA256_End(SHA256_CTX* context, char buffer[]) {
        sha2_byte       digest[SHA256_DIGEST_LENGTH], *d = digest;
        int             i;

        /* Sanity check: */
        assert(context != (SHA256_CTX*)0);

        if (buffer != (char*)0) {
                apr__SHA256_Final(digest, context);

                for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
                        *buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
                        *buffer++ = sha2_hex_digits[*d & 0x0f];
                        d++;
                }
                *buffer = (char)0;
        } else {
                MEMSET_BZERO(context, sizeof(*context));
        }
        MEMSET_BZERO(digest, SHA256_DIGEST_LENGTH);
        return buffer;
}