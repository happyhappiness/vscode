static const char *
make_auth_header(const cachemgr_request * req)
{
    static char buf[1024];
    size_t stringLength = 0;

    if (!req->passwd)
        return "";

    int bufLen = snprintf(buf, sizeof(buf), "%s:%s",
                          req->user_name ? req->user_name : "",
                          req->passwd);

    int encodedLen = base64_encode_len(bufLen);
    if (encodedLen <= 0)
        return "";

    uint8_t *str64 = static_cast<uint8_t*>(xmalloc(encodedLen));
    struct base64_encode_ctx ctx;
    base64_encode_init(&ctx);
    size_t blen = base64_encode_update(&ctx, str64, bufLen, reinterpret_cast<uint8_t*>(buf));
    blen += base64_encode_final(&ctx, str64+blen);
    str64[blen] = '\0';

    stringLength += snprintf(buf, sizeof(buf), "Authorization: Basic %.*s\r\n", (int)blen, str64);

    assert(stringLength < sizeof(buf));

    snprintf(&buf[stringLength], sizeof(buf) - stringLength, "Proxy-Authorization: Basic %.*s\r\n", (int)blen, str64);

    xfree(str64);
    return buf;
}