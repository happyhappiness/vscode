void
Auth::Ntlm::UserRequest::HandleReply(void *data, const Helper::Reply &reply)
{
    Auth::StateData *r = static_cast<Auth::StateData *>(data);

    debugs(29, 8, HERE << "helper: '" << reply.whichServer << "' sent us reply=" << reply);

    if (!cbdataReferenceValid(r->data)) {
        debugs(29, DBG_IMPORTANT, "ERROR: NTLM Authentication invalid callback data. helper '" << reply.whichServer << "'.");
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

    Auth::Ntlm::UserRequest *lm_request = dynamic_cast<Auth::Ntlm::UserRequest *>(auth_user_request.getRaw());
    assert(lm_request != NULL);
    assert(lm_request->waiting);

    lm_request->waiting = 0;
    safe_free(lm_request->client_blob);

    assert(auth_user_request->user() != NULL);
    assert(auth_user_request->user()->auth_type == Auth::AUTH_NTLM);

    if (lm_request->authserver == NULL)
        lm_request->authserver = reply.whichServer.get(); // XXX: no locking?
    else
        assert(reply.whichServer == lm_request->authserver);

    switch (reply.result) {
    case Helper::TT:
        /* we have been given a blob to send to the client */
        safe_free(lm_request->server_blob);
        lm_request->request->flags.mustKeepalive = true;
        if (lm_request->request->flags.proxyKeepalive) {
            const char *serverBlob = reply.notes.findFirst("token");
            lm_request->server_blob = xstrdup(serverBlob);
            auth_user_request->user()->credentials(Auth::Handshake);
            auth_user_request->setDenyMessage("Authentication in progress");
            debugs(29, 4, HERE << "Need to challenge the client with a server token: '" << serverBlob << "'");
        } else {
            auth_user_request->user()->credentials(Auth::Failed);
            auth_user_request->setDenyMessage("NTLM authentication requires a persistent connection");
        }
        break;

    case Helper::Okay: {
        /* we're finished, release the helper */
        const char *userLabel = reply.notes.findFirst("user");
        if (!userLabel) {
            auth_user_request->user()->credentials(Auth::Failed);
            safe_free(lm_request->server_blob);
            lm_request->releaseAuthServer();
            debugs(29, DBG_CRITICAL, "ERROR: NTLM Authentication helper returned no username. Result: " << reply);
            break;
        }
        auth_user_request->user()->username(userLabel);
        auth_user_request->setDenyMessage("Login successful");
        safe_free(lm_request->server_blob);
        lm_request->releaseAuthServer();

        debugs(29, 4, HERE << "Successfully validated user via NTLM. Username '" << userLabel << "'");
        /* connection is authenticated */
        debugs(29, 4, HERE << "authenticated user " << auth_user_request->user()->username());
        /* see if this is an existing user */
        auto local_auth_user = lm_request->user();
        auto cached_user = Auth::Ntlm::User::Cache()->lookup(auth_user_request->user()->userKey());
        if (!cached_user) {
            local_auth_user->addToNameCache();
        } else {
            /* we can't seamlessly recheck the username due to the
             * challenge-response nature of the protocol.
             * Just free the temporary auth_user after merging as
             * much of it new state into the existing one as possible */
            cached_user->absorb(local_auth_user);
            /* from here on we are working with the original cached credentials. */
            local_auth_user = cached_user;
            auth_user_request->user(local_auth_user);
        }
        /* set these to now because this is either a new login from an
         * existing user or a new user */
        local_auth_user->expiretime = current_time.tv_sec;
        auth_user_request->user()->credentials(Auth::Ok);
        debugs(29, 4, HERE << "Successfully validated user via NTLM. Username '" << auth_user_request->user()->username() << "'");
    }
    break;

    case Helper::Error:
        /* authentication failure (wrong password, etc.) */
        auth_user_request->denyMessageFromHelper("NTLM", reply);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        lm_request->releaseAuthServer();
        debugs(29, 4, "Failed validating user via NTLM. Result: " << reply);
        break;

    case Helper::Unknown:
        debugs(29, DBG_IMPORTANT, "ERROR: NTLM Authentication Helper '" << reply.whichServer << "' crashed!.");
    /* continue to the next case */

    case Helper::TimedOut:
    case Helper::BrokenHelper:
        /* TODO kick off a refresh process. This can occur after a YR or after
         * a KK. If after a YR release the helper and resubmit the request via
         * Authenticate NTLM start.
         * If after a KK deny the user's request w/ 407 and mark the helper as
         * Needing YR. */
        if (reply.result == Helper::Unknown)
            auth_user_request->setDenyMessage("Internal Error");
        else
            auth_user_request->denyMessageFromHelper("NTLM", reply);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        lm_request->releaseAuthServer();
        debugs(29, DBG_IMPORTANT, "ERROR: NTLM Authentication validating user. Result: " << reply);
        break;
    }

    if (lm_request->request) {
        HTTPMSGUNLOCK(lm_request->request);
        lm_request->request = NULL;
    }
    r->handler(r->data);
    delete r;
}