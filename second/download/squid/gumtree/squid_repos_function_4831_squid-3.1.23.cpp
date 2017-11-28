void
AuthUserRequest::addReplyAuthHeader(HttpReply * rep, AuthUserRequest * auth_user_request, HttpRequest * request, int accelerated, int internal)
/* send the auth types we are configured to support (and have compiled in!) */
{
    http_hdr_type type;

    switch (rep->sline.status) {

    case HTTP_PROXY_AUTHENTICATION_REQUIRED:
        /* Proxy authorisation needed */
        type = HDR_PROXY_AUTHENTICATE;
        break;

    case HTTP_UNAUTHORIZED:
        /* WWW Authorisation needed */
        type = HDR_WWW_AUTHENTICATE;
        break;

    default:
        /* Keep GCC happy */
        /* some other HTTP status */
        type = HDR_ENUM_END;
        break;
    }

    debugs(29, 9, "authenticateFixHeader: headertype:" << type << " authuser:" << auth_user_request);

    if (((rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
            || (rep->sline.status == HTTP_UNAUTHORIZED)) && internal)
        /* this is a authenticate-needed response */
    {

        if ((auth_user_request != NULL) && authenticateDirection(auth_user_request) == 1)
            /* scheme specific */
            auth_user_request->user()->config->fixHeader(auth_user_request, rep, type, request);
        else {
            /* call each configured & running authscheme */

            for (authConfig::iterator  i = Config.authConfiguration.begin(); i != Config.authConfiguration.end(); ++i) {
                AuthConfig *scheme = *i;

                if (scheme->active())
                    scheme->fixHeader(NULL, rep, type, request);
                else
                    debugs(29, 4, "authenticateFixHeader: Configured scheme " << scheme->type() << " not Active");
            }
        }

    }
    /*
     * allow protocol specific headers to be _added_ to the existing
     * response - ie digest auth
     */

    if (auth_user_request != NULL) {
        auth_user_request->addHeader(rep, accelerated);
        if (auth_user_request->lastReply != AUTH_AUTHENTICATED)
            auth_user_request->lastReply = AUTH_ACL_CANNOT_AUTHENTICATE;
    }
}