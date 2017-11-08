char* apr__SHA256_Data(const sha2_byte* data, size_t len, char digest[SHA256_DIGEST_STRING_LENGTH]) {
        SHA256_CTX      context;

        apr__SHA256_Init(&context);
        apr__SHA256_Update(&context, data, len);
        return apr__SHA256_End(&context, digest);
}