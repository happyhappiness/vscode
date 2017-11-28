const char *
urlCanonical(HttpRequest * request)
{
    LOCAL_ARRAY(char, portbuf, 32);
    LOCAL_ARRAY(char, urlbuf, MAX_URL);

    if (request->canonical)
        return request->canonical;

    if (request->url.getScheme() == AnyP::PROTO_URN) {
        snprintf(urlbuf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->urlpath));
    } else {
        switch (request->method.id()) {

        case Http::METHOD_CONNECT:
            snprintf(urlbuf, MAX_URL, "%s:%d", request->GetHost(), request->port);
            break;

        default: {
            portbuf[0] = '\0';

            if (request->port != urlDefaultPort(request->url.getScheme()))
                snprintf(portbuf, 32, ":%d", request->port);

            snprintf(urlbuf, MAX_URL, "%s://%s%s%s%s" SQUIDSTRINGPH,
                     request->url.getScheme().c_str(),
                     request->login,
                     *request->login ? "@" : null_string,
                     request->GetHost(),
                     portbuf,
                     SQUIDSTRINGPRINT(request->urlpath));
        }
        }
    }

    return (request->canonical = xstrdup(urlbuf));
}