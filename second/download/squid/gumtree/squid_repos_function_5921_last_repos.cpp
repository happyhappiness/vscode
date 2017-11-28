static bool
token_decode(size_t *decodedLen, uint8_t decoded[], const char *buf)
{
    struct base64_decode_ctx ctx;
    base64_decode_init(&ctx);
    if (!base64_decode_update(&ctx, decodedLen, decoded, strlen(buf), reinterpret_cast<const uint8_t*>(buf)) ||
            !base64_decode_final(&ctx)) {
        SEND_BH("message=\"base64 decode failed\"");
        fprintf(stderr, "ERROR: base64 decoding failed for: '%s'\n", buf);
        return false;
    }
    return true;
}