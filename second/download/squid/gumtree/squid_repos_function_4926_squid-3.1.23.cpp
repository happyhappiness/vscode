void
AuthNTLMUserRequest::authenticate(HttpRequest * aRequest, ConnStateData * conn, http_hdr_type type)
{
    const char *proxy_auth, *blob;

    /* TODO: rename this!! */
    AuthUser *local_auth_user;

    local_auth_user = user();
    assert(local_auth_user);
    assert(local_auth_user->auth_type == AUTH_NTLM);
    assert (this);

    /* Check that we are in the client side, where we can generate
     * auth challenges */

    if (conn == NULL || !cbdataReferenceValid(conn)) {
        auth_state = AUTHENTICATE_STATE_FAILED;
        debugs(29, 1, "AuthNTLMUserRequest::authenticate: attempt to perform authentication without a connection!");
        return;
    }

    if (waiting) {
        debugs(29, 1, "AuthNTLMUserRequest::authenticate: waiting for helper reply!");
        return;
    }

    if (server_blob) {
        debugs(29, 2, "AuthNTLMUserRequest::authenticate: need to challenge client '" << server_blob << "'!");
        return;
    }

    /* get header */
    proxy_auth = aRequest->header.getStr(type);

    /* locate second word */
    blob = proxy_auth;

    /* if proxy_auth is actually NULL, we'd better not manipulate it. */
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
        /* we've received a ntlm request. pass to a helper */
        debugs(29, 9, "AuthNTLMUserRequest::authenticate: auth state ntlm none. Received blob: '" << proxy_auth << "'");
        auth_state = AUTHENTICATE_STATE_INITIAL;
        safe_free(client_blob);
        client_blob=xstrdup(blob);
        conn->auth_type = AUTH_NTLM;
        assert(conn->auth_user_request == NULL);
        conn->auth_user_request = this;
        AUTHUSERREQUESTLOCK(conn->auth_user_request, "conn");
        request = aRequest;
        HTTPMSGLOCK(request);
        return;

        break;

    case AUTHENTICATE_STATE_INITIAL:
        debugs(29, 1, "AuthNTLMUserRequest::authenticate: need to ask helper");

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
        fatal("AuthNTLMUserRequest::authenticate: unexpect auth state DONE! Report a bug to the squid developers.\n");

        break;

    case AUTHENTICATE_STATE_FAILED:
        /* we've failed somewhere in authentication */
        debugs(29, 9, "AuthNTLMUserRequest::authenticate: auth state ntlm failed. " << proxy_auth);

        return;

        break;
    }

    return;
}