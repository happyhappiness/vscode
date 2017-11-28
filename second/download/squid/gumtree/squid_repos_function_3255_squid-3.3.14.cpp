const char *
urlCanonical(HttpRequest * request)
{
    LOCAL_ARRAY(char, portbuf, 32);
/// \todo AYJ: Performance: making this a ptr and allocating when needed will be better than a write and future xstrdup().
    LOCAL_ARRAY(char, urlbuf, MAX_URL);

    if (request->canonical)
        return request->canonical;

    if (request->protocol == AnyP::PROTO_URN) {
        snprintf(urlbuf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->urlpath));
    } else {
/// \todo AYJ: this could use "if..else and method == METHOD_CONNECT" easier.
        switch (request->method.id()) {

        case METHOD_CONNECT:
            snprintf(urlbuf, MAX_URL, "%s:%d", request->GetHost(), request->port);
            break;

        default:
            portbuf[0] = '\0';

            if (request->port != urlDefaultPort(request->protocol))
                snprintf(portbuf, 32, ":%d", request->port);

            const URLScheme sch = request->protocol; // temporary, until bug 1961 URL handling is fixed.
            snprintf(urlbuf, MAX_URL, "%s://%s%s%s%s" SQUIDSTRINGPH,
                     sch.const_str(),
                     request->login,
                     *request->login ? "@" : null_string,
                     request->GetHost(),
                     portbuf,
                     SQUIDSTRINGPRINT(request->urlpath));

            break;
        }
    }

    return (request->canonical = xstrdup(urlbuf));
}