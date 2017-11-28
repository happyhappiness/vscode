auth_acl_t

AuthUserRequest::tryToAuthenticateAndSetAuthUser(AuthUserRequest ** auth_user_request, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, IpAddress &src_addr)
{
    /* If we have already been called, return the cached value */
    AuthUserRequest *t = authTryGetUser (auth_user_request, conn, request);

    if (t && t->lastReply != AUTH_ACL_CANNOT_AUTHENTICATE
            && t->lastReply != AUTH_ACL_HELPER) {
        if (!*auth_user_request)
            *auth_user_request = t;

        if (!request->auth_user_request && t->lastReply == AUTH_AUTHENTICATED) {
            request->auth_user_request = t;
            AUTHUSERREQUESTLOCK(request->auth_user_request, "request");
        }
        return t->lastReply;
    }

    /* ok, call the actual authenticator routine. */
    auth_acl_t result = authenticate(auth_user_request, headertype, request, conn, src_addr);

    t = authTryGetUser (auth_user_request, conn, request);

    if (t && result != AUTH_ACL_CANNOT_AUTHENTICATE &&
            result != AUTH_ACL_HELPER)
        t->lastReply = result;

    return result;
}