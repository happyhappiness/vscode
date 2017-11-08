char* SHA384_Data(const sha2_byte* data, size_t len, char digest[SHA384_DIGEST_STRING_LENGTH]) {
        SHA384_CTX      context;

        SHA384_Init(&context);
        SHA384_Update(&context, data, len);
        return SHA384_End(&context, digest);
}