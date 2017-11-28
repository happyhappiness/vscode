char *
urlCanonicalClean(const HttpRequest * request)
{
    LOCAL_ARRAY(char, buf, MAX_URL);
    LOCAL_ARRAY(char, portbuf, 32);
    LOCAL_ARRAY(char, loginbuf, MAX_LOGIN_SZ + 1);
    char *t;

    if (request->url.getScheme() == AnyP::PROTO_URN) {
        snprintf(buf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->urlpath));
    } else {
        switch (request->method.id()) {

        case Http::METHOD_CONNECT:
            snprintf(buf, MAX_URL, "%s:%d", request->GetHost(), request->port);
            break;

        default: {
            portbuf[0] = '\0';

            if (request->port != urlDefaultPort(request->url.getScheme()))
                snprintf(portbuf, 32, ":%d", request->port);

            loginbuf[0] = '\0';

            if ((int) strlen(request->login) > 0) {
                strcpy(loginbuf, request->login);

                if ((t = strchr(loginbuf, ':')))
                    *t = '\0';

                strcat(loginbuf, "@");
            }

            snprintf(buf, MAX_URL, "%s://%s%s%s" SQUIDSTRINGPH,
                     request->url.getScheme().c_str(),
                     loginbuf,
                     request->GetHost(),
                     portbuf,
                     SQUIDSTRINGPRINT(request->urlpath));

            // strip arguments AFTER a question-mark
            if (Config.onoff.strip_query_terms)
                if ((t = strchr(buf, '?')))
                    *(++t) = '\0';
        }
        }
    }

    if (stringHasCntl(buf))
        xstrncpy(buf, rfc1738_escape_unescaped(buf), MAX_URL);

    return buf;
}