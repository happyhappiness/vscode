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

    char *str64 = static_cast<char*>(xmalloc(encodedLen));
    base64_encode_str(str64, encodedLen, buf, bufLen);

    stringLength += snprintf(buf, sizeof(buf), "Authorization: Basic %s\r\n", str64);

    assert(stringLength < sizeof(buf));

    snprintf(&buf[stringLength], sizeof(buf) - stringLength, "Proxy-Authorization: Basic %s\r\n", str64);

    xfree(str64);
    return buf;
}