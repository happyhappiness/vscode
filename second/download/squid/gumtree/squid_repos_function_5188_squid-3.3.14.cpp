void
Auth::UserRequest::addReplyAuthHeader(HttpReply * rep, Auth::UserRequest::Pointer auth_user_request, HttpRequest * request, int accelerated, int internal)
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

    debugs(29, 9, HERE << "headertype:" << type << " authuser:" << auth_user_request);

    if (((rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
            || (rep->sline.status == HTTP_UNAUTHORIZED)) && internal)
        /* this is a authenticate-needed response */
    {

        if (auth_user_request != NULL && auth_user_request->direction() == Auth::CRED_CHALLENGE)
            /* add the scheme specific challenge header to the response */
            auth_user_request->user()->config->fixHeader(auth_user_request, rep, type, request);
        else {
            /* call each configured & running authscheme */

            for (Auth::ConfigVector::iterator  i = Auth::TheConfig.begin(); i != Auth::TheConfig.end(); ++i) {
                Auth::Config *scheme = *i;

                if (scheme->active())
                    scheme->fixHeader(NULL, rep, type, request);
                else
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