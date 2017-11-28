static const char *
make_auth_header(const cachemgr_request * req)
{
    static char buf[1024];
    size_t stringLength = 0;
    const char *str64;

    if (!req->passwd)
        return "";

    snprintf(buf, sizeof(buf), "%s:%s",
             req->user_name ? req->user_name : "",
             req->passwd);

    str64 = base64_encode(buf);

    stringLength += snprintf(buf, sizeof(buf), "Authorization: Basic %s\r\n", str64);

    assert(stringLength < sizeof(buf));

    snprintf(&buf[stringLength], sizeof(buf) - stringLength, "Proxy-Authorization: Basic %s\r\n", str64);

    xxfree(str64);
    return buf;
}