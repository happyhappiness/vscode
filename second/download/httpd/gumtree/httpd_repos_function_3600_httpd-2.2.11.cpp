char* apr__SHA384_Data(const sha2_byte* data, size_t len, char digest[SHA384_DIGEST_STRING_LENGTH]) {
        SHA384_CTX      context;

        apr__SHA384_Init(&context);
        apr__SHA384_Update(&context, data, len);
        return apr__SHA384_End(&context, digest);
}