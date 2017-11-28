void
Auth::Ntlm::UserRequest::authenticate(HttpRequest * aRequest, ConnStateData * conn, Http::HdrType type)
{
    /* Check that we are in the client side, where we can generate
     * auth challenges */

    if (conn == NULL || !cbdataReferenceValid(conn)) {
        user()->credentials(Auth::Failed);
        debugs(29, DBG_IMPORTANT, "WARNING: NTLM Authentication attempt to perform authentication without a connection!");
        return;
    }

    if (waiting) {
        debugs(29, DBG_IMPORTANT, "WARNING: NTLM Authentication waiting for helper reply!");
        return;
    }

    if (server_blob) {
        debugs(29, 2, HERE << "need to challenge client '" << server_blob << "'!");
        return;
    }

    /* get header */
    const char *proxy_auth = aRequest->header.getStr(type);

    /* locate second word */
    const char *blob = proxy_auth;

    /* if proxy_auth is actually NULL, we'd better not manipulate it. */
    if (blob) {
        while (xisspace(*blob) && *blob)
            ++blob;

        while (!xisspace(*blob) && *blob)
            ++blob;

        while (xisspace(*blob) && *blob)
            ++blob;
    }

    switch (user()->credentials()) {

    case Auth::Unchecked:
        /* we've received a ntlm request. pass to a helper */
        debugs(29, 9, HERE << "auth state ntlm none. Received blob: '" << proxy_auth << "'");
        user()->credentials(Auth::Pending);
        safe_free(client_blob);
        client_blob=xstrdup(blob);
        assert(conn->getAuth() == NULL);
        conn->setAuth(this, "new NTLM handshake request");
        request = aRequest;
        HTTPMSGLOCK(request);
        break;

    case Auth::Pending:
        debugs(29, DBG_IMPORTANT, HERE << "need to ask helper");
        break;

    case Auth::Handshake:
        /* we should have received a blob from the client. Hand it off to
         * some helper */
        safe_free(client_blob);
        client_blob = xstrdup(blob);
        if (request)
            HTTPMSGUNLOCK(request);
        request = aRequest;
        HTTPMSGLOCK(request);
        break;

    case Auth::Ok:
        fatal("Auth::Ntlm::UserRequest::authenticate: unexpect auth state DONE! Report a bug to the squid developers.\n");
        break;

    case Auth::Failed:
        /* we've failed somewhere in authentication */
        debugs(29, 9, HERE << "auth state ntlm failed. " << proxy_auth);
        break;
    }
}