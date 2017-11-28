char *
urlCanonicalClean(const HttpRequest * request)
{
    LOCAL_ARRAY(char, buf, MAX_URL);
    LOCAL_ARRAY(char, portbuf, 32);
    LOCAL_ARRAY(char, loginbuf, MAX_LOGIN_SZ + 1);
    char *t;

    if (request->protocol == AnyP::PROTO_URN) {
        snprintf(buf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->urlpath));
    } else if (request->method.id() == Http::METHOD_CONNECT) {
        snprintf(buf, MAX_URL, "%s:%d", request->GetHost(), request->port);
    } else {
        portbuf[0] = '\0';

        if (request->port != urlDefaultPort(request->protocol))
            snprintf(portbuf, 32, ":%d", request->port);

        loginbuf[0] = '\0';

        if ((int) strlen(request->login) > 0) {
            strcpy(loginbuf, request->login);

            if ((t = strchr(loginbuf, ':')))
                *t = '\0';

            strcat(loginbuf, "@");
        }

        const URLScheme sch = request->protocol; // temporary, until bug 1961 URL handling is fixed.
        snprintf(buf, MAX_URL, "%s://%s%s%s" SQUIDSTRINGPH,
                 sch.const_str(),
                 loginbuf,
                 request->GetHost(),
                 portbuf,
                 SQUIDSTRINGPRINT(request->urlpath));
        /*
         * strip arguments AFTER a question-mark
         */

        if (Config.onoff.strip_query_terms)
            if ((t = strchr(buf, '?')))
                *(++t) = '\0';
    }

    if (stringHasCntl(buf))
        xstrncpy(buf, rfc1738_escape_unescaped(buf), MAX_URL);

    return buf;
}