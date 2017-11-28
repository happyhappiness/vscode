AuthAclState
Auth::UserRequest::tryToAuthenticateAndSetAuthUser(Auth::UserRequest::Pointer * aUR, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, Ip::Address &src_addr)
{
    // If we have already been called, return the cached value
    Auth::UserRequest::Pointer t = authTryGetUser(*aUR, conn, request);

    if (t != NULL && t->lastReply != AUTH_ACL_CANNOT_AUTHENTICATE && t->lastReply != AUTH_ACL_HELPER) {
        if (*aUR == NULL)
            *aUR = t;

        if (request->auth_user_request == NULL && t->lastReply == AUTH_AUTHENTICATED) {
            request->auth_user_request = t;
        }
        return t->lastReply;
    }

    // ok, call the actual authenticator routine.
    AuthAclState result = authenticate(aUR, headertype, request, conn, src_addr);

    // auth process may have changed the UserRequest we are dealing with
    t = authTryGetUser(*aUR, conn, request);

    if (t != NULL && result != AUTH_ACL_CANNOT_AUTHENTICATE && result != AUTH_ACL_HELPER)
        t->lastReply = result;

    return result;
}