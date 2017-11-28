static HttpRequest *
urlParseFinish(const HttpRequestMethod& method,
               const protocol_t protocol,
               const char *const urlpath,
               const char *const host,
               const char *const login,
               const int port,
               HttpRequest *request)
{
    if (NULL == request)
        request = new HttpRequest(method, protocol, urlpath);
    else {
        request->initHTTP(method, protocol, urlpath);
        safe_free(request->canonical);
    }

    request->SetHost(host);
    xstrncpy(request->login, login, MAX_LOGIN_SZ);
    request->port = (unsigned short) port;
    return request;
}