void
Auth::UserRequest::addReplyAuthHeader(HttpReply * rep, Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated, int internal)
/* send the auth types we are configured to support (and have compiled in!) */
{
    Http::HdrType type;

    switch (rep->sline.status()) {

    case Http::scProxyAuthenticationRequired:
        /* Proxy authorisation needed */
        type = Http::HdrType::PROXY_AUTHENTICATE;
        break;

    case Http::scUnauthorized:
        /* WWW Authorisation needed */
        type = Http::HdrType::WWW_AUTHENTICATE;
        break;

    default:
        /* Keep GCC happy */
        /* some other HTTP status */
        type = Http::HdrType::BAD_HDR;
        break;
    }

    debugs(29, 9, "headertype:" << type << " authuser:" << auth_user_request);

    if (((rep->sline.status() == Http::scProxyAuthenticationRequired)
            || (rep->sline.status() == Http::scUnauthorized)) && internal)
        /* this is a authenticate-needed response */
    {

        if (auth_user_request != NULL && auth_user_request->direction() == Auth::CRED_CHALLENGE)
            /* add the scheme specific challenge header to the response */
            auth_user_request->user()->config->fixHeader(auth_user_request, rep, type, request);
        else {
            /* call each configured & running authscheme */

            for (Auth::ConfigVector::iterator  i = Auth::TheConfig.begin(); i != Auth::TheConfig.end(); ++i) {
                Auth::Config *scheme = *i;

                if (scheme->active()) {
                    if (auth_user_request != NULL && auth_user_request->scheme()->type() == scheme->type())
                        scheme->fixHeader(auth_user_request, rep, type, request);
                    else
                        scheme->fixHeader(NULL, rep, type, request);
                } else
                    debugs(29, 4, HERE << "Configured scheme " << scheme->type() << " not Active");
            }
        }

    }

    /*
     * allow protocol specific headers to be _added_ to the existing
     * response - currently Digest or Negotiate auth
     */
    if (auth_user_request != NULL) {
        auth_user_request->addAuthenticationInfoHeader(rep, accelerated);
        if (auth_user_request->lastReply != AUTH_AUTHENTICATED)
            auth_user_request->lastReply = AUTH_ACL_CANNOT_AUTHENTICATE;
    }
}