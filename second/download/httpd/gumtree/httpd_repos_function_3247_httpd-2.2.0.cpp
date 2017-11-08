char* SHA256_Data(const sha2_byte* data, size_t len, char digest[SHA256_DIGEST_STRING_LENGTH]) {
        SHA256_CTX      context;

        SHA256_Init(&context);
        SHA256_Update(&context, data, len);
        return SHA256_End(&context, digest);
}