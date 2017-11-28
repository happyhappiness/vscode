static void
authenticateNegotiateHandleReply(void *data, void *lastserver, char *reply)
{
    authenticateStateData *r = static_cast<authenticateStateData *>(data);

    int valid;
    char *blob, *arg = NULL;

    AuthUserRequest *auth_user_request;
    AuthUser *auth_user;
    NegotiateUser *negotiate_user;
    AuthNegotiateUserRequest *negotiate_request;

    debugs(29, 8, "authenticateNegotiateHandleReply: helper: '" << lastserver << "' sent us '" << (reply ? reply : "<NULL>") << "'");
    valid = cbdataReferenceValid(r->data);

    if (!valid) {
        debugs(29, 1, "authenticateNegotiateHandleReply: invalid callback data. helper '" << lastserver << "'.");
        cbdataReferenceDone(r->data);
        authenticateStateFree(r);
        return;
    }

    if (!reply) {
        debugs(29, 1, "authenticateNegotiateHandleReply: Helper '" << lastserver << "' crashed!.");
        reply = (char *)"BH Internal error";
    }

    auth_user_request = r->auth_user_request;
    assert(auth_user_request != NULL);
    negotiate_request = dynamic_cast<AuthNegotiateUserRequest *>(auth_user_request);

    assert(negotiate_request != NULL);
    assert(negotiate_request->waiting);
    negotiate_request->waiting = 0;
    safe_free(negotiate_request->client_blob);

    auth_user = negotiate_request->user();
    assert(auth_user != NULL);
    assert(auth_user->auth_type == AUTH_NEGOTIATE);
    negotiate_user = dynamic_cast<negotiate_user_t *>(auth_user_request->user());

    assert(negotiate_user != NULL);

    if (negotiate_request->authserver == NULL)
        negotiate_request->authserver = static_cast<helper_stateful_server*>(lastserver);
    else
        assert(negotiate_request->authserver == lastserver);

    /* seperate out the useful data */
    blob = strchr(reply, ' ');

    if (blob) {
        blob++;
        arg = strchr(blob + 1, ' ');
    } else {
        arg = NULL;
    }

    if (strncasecmp(reply, "TT ", 3) == 0) {
        /* we have been given a blob to send to the client */
        if (arg)
            *arg++ = '\0';
        safe_free(negotiate_request->server_blob);
        negotiate_request->request->flags.must_keepalive = 1;
        if (negotiate_request->request->flags.proxy_keepalive) {
            negotiate_request->server_blob = xstrdup(blob);
            negotiate_request->auth_state = AUTHENTICATE_STATE_IN_PROGRESS;
            auth_user_request->denyMessage("Authentication in progress");
            debugs(29, 4, "authenticateNegotiateHandleReply: Need to challenge the client with a server blob '" << blob << "'");
        } else {
            negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;
            auth_user_request->denyMessage("NTLM authentication requires a persistent connection");
        }
    } else if (strncasecmp(reply, "AF ", 3) == 0 && arg != NULL) {
        /* we're finished, release the helper */

        if (arg)
            *arg++ = '\0';

        negotiate_user->username(arg);

        auth_user_request->denyMessage("Login successful");

        safe_free(negotiate_request->server_blob);

        negotiate_request->server_blob = xstrdup(blob);

        negotiate_request->releaseAuthServer();

        negotiate_request->auth_state = AUTHENTICATE_STATE_DONE;

        debugs(29, 4, "authenticateNegotiateHandleReply: Successfully validated user via Negotiate. Username '" << blob << "'");

        /* connection is authenticated */
        debugs(29, 4, "AuthNegotiateUserRequest::authenticate: authenticated user " << negotiate_user->username());
        /* see if this is an existing user with a different proxy_auth
         * string */
        AuthUserHashPointer *usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, negotiate_user->username()));
        AuthUser *local_auth_user = negotiate_request->user();
        while (usernamehash && (usernamehash->user()->auth_type != AUTH_NEGOTIATE || strcmp(usernamehash->user()->username(), negotiate_user->username()) != 0))
            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
        if (usernamehash) {
            /* we can't seamlessly recheck the username due to the
             * challenge-response nature of the protocol.
             * Just free the temporary auth_user */
            usernamehash->user()->absorb(local_auth_user);
            //authenticateAuthUserMerge(local_auth_user, usernamehash->user());
            local_auth_user = usernamehash->user();
            negotiate_request->_auth_user = local_auth_user;
        } else {
            /* store user in hash's */
            local_auth_user->addToNameCache();
            // authenticateUserNameCacheAdd(local_auth_user);
        }
        /* set these to now because this is either a new login from an
         * existing user or a new user */
        local_auth_user->expiretime = current_time.tv_sec;
        negotiate_request->releaseAuthServer();
        negotiate_request->auth_state = AUTHENTICATE_STATE_DONE;

    } else if (strncasecmp(reply, "NA ", 3) == 0 && arg != NULL) {
        /* authentication failure (wrong password, etc.) */

        if (arg)
            *arg++ = '\0';

        auth_user_request->denyMessage(arg);

        negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;

        safe_free(negotiate_request->server_blob);

        negotiate_request->server_blob = xstrdup(blob);

        negotiate_request->releaseAuthServer();

        debugs(29, 4, "authenticateNegotiateHandleReply: Failed validating user via Negotiate. Error returned '" << blob << "'");
    } else if (strncasecmp(reply, "BH ", 3) == 0) {
        /* TODO kick off a refresh process. This can occur after a YR or after
         * a KK. If after a YR release the helper and resubmit the request via
         * Authenticate Negotiate start.
         * If after a KK deny the user's request w/ 407 and mark the helper as
         * Needing YR. */
        auth_user_request->denyMessage(blob);
        negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;
        safe_free(negotiate_request->server_blob);
        negotiate_request->releaseAuthServer();
        debugs(29, 1, "authenticateNegotiateHandleReply: Error validating user via Negotiate. Error returned '" << reply << "'");
    } else {
        /* protocol error */
        fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply);
    }

    if (negotiate_request->request) {
        HTTPMSGUNLOCK(negotiate_request->request);
        negotiate_request->request = NULL;
    }
    r->handler(r->data, NULL);
    cbdataReferenceDone(r->data);
    authenticateStateFree(r);
}