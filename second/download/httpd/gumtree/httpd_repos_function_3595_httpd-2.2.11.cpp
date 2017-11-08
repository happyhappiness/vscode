char* apr__SHA512_Data(const sha2_byte* data, size_t len, char digest[SHA512_DIGEST_STRING_LENGTH]) {
        SHA512_CTX      context;

        apr__SHA512_Init(&context);
        apr__SHA512_Update(&context, data, len);
        return apr__SHA512_End(&context, digest);
}