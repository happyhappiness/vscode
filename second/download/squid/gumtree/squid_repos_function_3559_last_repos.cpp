void Adaptation::Icap::ModXact::makeUsernameHeader(const HttpRequest *request, MemBuf &buf)
{
#if USE_AUTH
    struct base64_encode_ctx ctx;
    base64_encode_init(&ctx);

    const char *value = NULL;
    if (request->auth_user_request != NULL) {
        value = request->auth_user_request->username();
    } else if (request->extacl_user.size() > 0) {
        value = request->extacl_user.termedBuf();
    }

    if (value) {
        if (TheConfig.client_username_encode) {
            uint8_t base64buf[base64_encode_len(MAX_LOGIN_SZ)];
            size_t resultLen = base64_encode_update(&ctx, base64buf, strlen(value), reinterpret_cast<const uint8_t*>(value));
            resultLen += base64_encode_final(&ctx, base64buf+resultLen);
            buf.appendf("%s: %.*s\r\n", TheConfig.client_username_header, (int)resultLen, base64buf);
        } else
            buf.appendf("%s: %s\r\n", TheConfig.client_username_header, value);
    }
#endif
}