char *
urlCanonicalClean(const HttpRequest * request)
{
    LOCAL_ARRAY(char, buf, MAX_URL);
    LOCAL_ARRAY(char, portbuf, 32);
    LOCAL_ARRAY(char, loginbuf, MAX_LOGIN_SZ + 1);
    char *t;

    if (request->protocol == PROTO_URN) {
        snprintf(buf, MAX_URL, "urn:" SQUIDSTRINGPH,
                 SQUIDSTRINGPRINT(request->urlpath));
    } else {
/// \todo AYJ: this could use "if..else and method == METHOD_CONNECT" easier.
        switch (request->method.id()) {

        case METHOD_CONNECT:
            snprintf(buf, MAX_URL, "%s:%d",
                     request->GetHost(),
                     request->port);
            break;

        default:
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

            snprintf(buf, MAX_URL, "%s://%s%s%s" SQUIDSTRINGPH,
                     ProtocolStr[request->protocol],
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

            break;
        }
    }

    if (stringHasCntl(buf))
        xstrncpy(buf, rfc1738_escape_unescaped(buf), MAX_URL);

    return buf;
}