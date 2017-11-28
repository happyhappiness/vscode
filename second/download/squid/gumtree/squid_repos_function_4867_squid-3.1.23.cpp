void
AuthNegotiateUserRequest::authenticate(HttpRequest * aRequest, ConnStateData * conn, http_hdr_type type)
{
    const char *proxy_auth, *blob;

    /** \todo rename this!! */
    AuthUser *local_auth_user;

    local_auth_user = user();
    assert(local_auth_user);
    assert(local_auth_user->auth_type == AUTH_NEGOTIATE);
    assert (this);

    /** Check that we are in the client side, where we can generate
     * auth challenges */

    if (conn == NULL) {
        auth_state = AUTHENTICATE_STATE_FAILED;
        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: attempt to perform authentication without a connection!");
        return;
    }

    if (waiting) {
        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: waiting for helper reply!");
        return;
    }

    if (server_blob) {
        debugs(29, 2, "AuthNegotiateUserRequest::authenticate: need to challenge client '" << server_blob << "'!");
        return;
    }

    /* get header */
    proxy_auth = aRequest->header.getStr(type);

    /* locate second word */
    blob = proxy_auth;

    if (blob) {
        while (xisspace(*blob) && *blob)
            blob++;

        while (!xisspace(*blob) && *blob)
            blob++;

        while (xisspace(*blob) && *blob)
            blob++;
    }

    switch (auth_state) {

    case AUTHENTICATE_STATE_NONE:
        /* we've received a negotiate request. pass to a helper */
        debugs(29, 9, "AuthNegotiateUserRequest::authenticate: auth state negotiate none. Received blob: '" << proxy_auth << "'");
        auth_state = AUTHENTICATE_STATE_INITIAL;
        safe_free(client_blob);
        client_blob=xstrdup(blob);
        conn->auth_type = AUTH_NEGOTIATE;
        assert(conn->auth_user_request == NULL);
        conn->auth_user_request = this;
        AUTHUSERREQUESTLOCK(conn->auth_user_request, "conn");
        request = aRequest;
        HTTPMSGLOCK(request);
        return;

        break;

    case AUTHENTICATE_STATE_INITIAL:
        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: need to ask helper");

        return;

        break;


    case AUTHENTICATE_STATE_IN_PROGRESS:
        /* we should have received a blob from the client. Hand it off to
         * some helper */
        safe_free(client_blob);

        client_blob = xstrdup (blob);

        if (request)
            HTTPMSGUNLOCK(request);
        request = aRequest;
        HTTPMSGLOCK(request);
        return;

        break;

    case AUTHENTICATE_STATE_DONE:
        fatal("AuthNegotiateUserRequest::authenticate: unexpect auth state DONE! Report a bug to the squid developers.\n");

        break;

    case AUTHENTICATE_STATE_FAILED:
        /* we've failed somewhere in authentication */
        debugs(29, 9, "AuthNegotiateUserRequest::authenticate: auth state negotiate failed. " << proxy_auth);

        return;

        break;
    }

    return;
}