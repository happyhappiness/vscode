char* SHA512_Data(const sha2_byte* data, size_t len, char digest[SHA512_DIGEST_STRING_LENGTH]) {
        SHA512_CTX      context;

        SHA512_Init(&context);
        SHA512_Update(&context, data, len);
        return SHA512_End(&context, digest);
}