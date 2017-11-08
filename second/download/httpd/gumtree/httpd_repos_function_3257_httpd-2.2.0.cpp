void SHA384_Update(SHA384_CTX* context, const sha2_byte* data, size_t len) {
        SHA512_Update((SHA512_CTX*)context, data, len);
}