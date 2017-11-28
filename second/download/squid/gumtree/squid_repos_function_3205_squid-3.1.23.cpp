const char *
urlCanonicalFakeHttps(const HttpRequest * request)
{
    LOCAL_ARRAY(char, buf, MAX_URL);

    // method CONNECT and port HTTPS
    if (request->method == METHOD_CONNECT && request->port == 443) {
        snprintf(buf, MAX_URL, "https://%s/*", request->GetHost());
        return buf;
    }

    // else do the normal complete canonical thing.
    return urlCanonicalClean(request);
}