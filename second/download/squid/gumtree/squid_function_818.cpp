void
Auth::Negotiate::UserRequest::HandleReply(void *data, void *lastserver, char *reply)
{
    Auth::StateData *r = static_cast<Auth::StateData *>(data);

    char *blob, *arg = NULL;

    debugs(29, 8, HERE << "helper: '" << lastserver << "' sent us '" << (reply ? reply : "<NULL>") << "'");

    if (!cbdataReferenceValid(r->data)) {
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication invalid callback data. helper '" << lastserver << "'.");
        delete r;
        return;
    }

    if (!reply) {
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication Helper '" << lastserver << "' crashed!.");
        reply = (char *)"BH Internal error";
    }

    Auth::UserRequest::Pointer auth_user_request = r->auth_user_request;
    assert(auth_user_request != NULL);

    Auth::Negotiate::UserRequest *lm_request = dynamic_cast<Auth::Negotiate::UserRequest *>(auth_user_request.getRaw());
    assert(lm_request != NULL);
    assert(lm_request->waiting);

    lm_request->waiting = 0;
    safe_free(lm_request->client_blob);

    assert(auth_user_request->user() != NULL);
    assert(auth_user_request->user()->auth_type == Auth::AUTH_NEGOTIATE);

    if (lm_request->authserver == NULL)
        lm_request->authserver = static_cast<helper_stateful_server*>(lastserver);
    else
        assert(lm_request->authserver == lastserver);

    /* seperate out the useful data */
    blob = strchr(reply, ' ');

    if (blob) {
        ++blob;
        arg = strchr(blob + 1, ' ');
    } else {
        arg = NULL;
    }

    if (strncasecmp(reply, "TT ", 3) == 0) {
        /* we have been given a blob to send to the client */
        if (arg) {
            *arg = '\0';
            ++arg;
        }
        safe_free(lm_request->server_blob);
        lm_request->request->flags.mustKeepalive = 1;
        if (lm_request->request->flags.proxyKeepalive) {
            lm_request->server_blob = xstrdup(blob);
            auth_user_request->user()->credentials(Auth::Handshake);
            auth_user_request->denyMessage("Authentication in progress");
            debugs(29, 4, HERE << "Need to challenge the client with a server blob '" << blob << "'");
        } else {
            auth_user_request->user()->credentials(Auth::Failed);
            auth_user_request->denyMessage("NTLM authentication requires a persistent connection");
        }
    } else if (strncasecmp(reply, "AF ", 3) == 0 && arg != NULL) {
        /* we're finished, release the helper */

        if (arg) {
            *arg = '\0';
            ++arg;
        }

        auth_user_request->user()->username(arg);
        auth_user_request->denyMessage("Login successful");
        safe_free(lm_request->server_blob);
        lm_request->server_blob = xstrdup(blob);
        lm_request->releaseAuthServer();

        /* connection is authenticated */
        debugs(29, 4, HERE << "authenticated user " << auth_user_request->user()->username());
        /* see if this is an existing user with a different proxy_auth
         * string */
        AuthUserHashPointer *usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, auth_user_request->user()->username()));
        Auth::User::Pointer local_auth_user = lm_request->user();
        while (usernamehash && (usernamehash->user()->auth_type != Auth::AUTH_NEGOTIATE ||
                                strcmp(usernamehash->user()->username(), auth_user_request->user()->username()) != 0))
            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
        if (usernamehash) {
            /* we can't seamlessly recheck the username due to the
             * challenge-response nature of the protocol.
             * Just free the temporary auth_user after merging as
             * much of it new state into the existing one as possible */
            usernamehash->user()->absorb(local_auth_user);
            /* from here on we are working with the original cached credentials. */
            local_auth_user = usernamehash->user();
            auth_user_request->user(local_auth_user);
        } else {
            /* store user in hash's */
            local_auth_user->addToNameCache();
        }
        /* set these to now because this is either a new login from an
         * existing user or a new user */
        local_auth_user->expiretime = current_time.tv_sec;
        auth_user_request->user()->credentials(Auth::Ok);
        debugs(29, 4, HERE << "Successfully validated user via Negotiate. Username '" << blob << "'");

    } else if (strncasecmp(reply, "NA ", 3) == 0 && arg != NULL) {
        /* authentication failure (wrong password, etc.) */

        if (arg) {
            *arg = '\0';
            ++arg;
        }

        auth_user_request->denyMessage(arg);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        lm_request->server_blob = xstrdup(blob);
        lm_request->releaseAuthServer();
        debugs(29, 4, HERE << "Failed validating user via Negotiate. Error returned '" << blob << "'");
    } else if (strncasecmp(reply, "BH ", 3) == 0) {
        /* TODO kick off a refresh process. This can occur after a YR or after
         * a KK. If after a YR release the helper and resubmit the request via
         * Authenticate Negotiate start.
         * If after a KK deny the user's request w/ 407 and mark the helper as
         * Needing YR. */
        auth_user_request->denyMessage(blob);
        auth_user_request->user()->credentials(Auth::Failed);
        safe_free(lm_request->server_blob);
        lm_request->releaseAuthServer();
        debugs(29, DBG_IMPORTANT, "ERROR: Negotiate Authentication validating user. Error returned '" << reply << "'");
    } else {
        /* protocol error */
        fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply);
    }

    if (lm_request->request) {
        HTTPMSGUNLOCK(lm_request->request);
        lm_request->request = NULL;
    }
    r->handler(r->data);
    delete r;
}