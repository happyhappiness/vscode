        debugs(29, 9, HERE << "auth state negotiate failed. " << proxy_auth);
        break;
    }
}

void
Auth::Negotiate::UserRequest::HandleReply(void *data, const HelperReply &reply)
{
    Auth::StateData *r = static_cast<Auth::StateData *>(data);

    debugs(29, 8, HERE << "helper: '" << reply.whichServer << "' sent us reply=" << reply);

    if (!cbdataReferenceValid(r->data)) {
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication invalid callback data. helper '" << reply.whichServer << "'.");
        delete r;
        return;
    }

    Auth::UserRequest::Pointer auth_user_request = r->auth_user_request;
    assert(auth_user_request != NULL);

    // add new helper kv-pair notes to the credentials object
    // so that any transaction using those credentials can access them
    auth_user_request->user()->notes.appendNewOnly(&reply.notes);
    // remove any private credentials detail which got added.
    auth_user_request->user()->notes.remove("token");

    Auth::Negotiate::UserRequest *lm_request = dynamic_cast<Auth::Negotiate::UserRequest *>(auth_user_request.getRaw());
    assert(lm_request != NULL);
    assert(lm_request->waiting);

    lm_request->waiting = 0;
    safe_free(lm_request->client_blob);

    assert(auth_user_request->user() != NULL);
    assert(auth_user_request->user()->auth_type == Auth::AUTH_NEGOTIATE);

    if (lm_request->authserver == NULL)
        lm_request->authserver = reply.whichServer.get(); // XXX: no locking?
    else
        assert(reply.whichServer == lm_request->authserver);

    switch (reply.result) {
    case HelperReply::TT:
        /* we have been given a blob to send to the client */
        safe_free(lm_request->server_blob);
        lm_request->request->flags.mustKeepalive = true;
        if (lm_request->request->flags.proxyKeepalive) {
            const char *tokenNote = reply.notes.findFirst("token");
            lm_request->server_blob = xstrdup(tokenNote);
            auth_user_request->user()->credentials(Auth::Handshake);
            auth_user_request->denyMessage("Authentication in progress");
            debugs(29, 4, HERE << "Need to challenge the client with a server token: '" << tokenNote << "'");
        } else {
            auth_user_request->user()->credentials(Auth::Failed);
            auth_user_request->denyMessage("Negotiate authentication requires a persistent connection");
        }
        break;

    case HelperReply::Okay: {
        const char *userNote = reply.notes.findFirst("user");
        const char *tokenNote = reply.notes.findFirst("token");
        if (userNote == NULL || tokenNote == NULL) {
            // XXX: handle a success with no username better
            /* protocol error */
            fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply.other().content());
            break;
        }

        /* we're finished, release the helper */
        auth_user_request->user()->username(userNote);
        auth_user_request->denyMessage("Login successful");
        safe_free(lm_request->server_blob);
        lm_request->server_blob = xstrdup(tokenNote);
        lm_request->releaseAuthServer();

        /* connection is authenticated */
        debugs(29, 4, HERE << "authenticated user " << auth_user_request->user()->username());
        /* see if this is an existing user with a different proxy_auth
         * string */
