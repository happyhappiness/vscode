auth_acl_t
AuthUserRequest::authenticate(AuthUserRequest ** auth_user_request, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, IpAddress &src_addr)
{
    const char *proxy_auth;
    assert(headertype != 0);

    proxy_auth = request->header.getStr(headertype);

    /*
     * a note on proxy_auth logix here:
     * proxy_auth==NULL -> unauthenticated request || already
     * authenticated connection so we test for an authenticated
     * connection when we recieve no authentication header.
     */

    if (((proxy_auth == NULL) && (!authenticateUserAuthenticated(authTryGetUser(auth_user_request,conn,request))))
            || (conn != NULL  && conn->auth_type == AUTH_BROKEN)) {
        /* no header or authentication failed/got corrupted - restart */
        debugs(29, 4, "authenticateAuthenticate: broken auth or no proxy_auth header. Requesting auth header.");
        /* something wrong with the AUTH credentials. Force a new attempt */

        if (conn != NULL) {
            conn->auth_type = AUTH_UNKNOWN;
            AUTHUSERREQUESTUNLOCK(conn->auth_user_request, "conn");
        }

        *auth_user_request = NULL;
        return AUTH_ACL_CHALLENGE;
    }

    /*
     * Is this an already authenticated connection with a new auth header?
     * No check for function required in the if: its compulsory for conn based
     * auth modules
     */
    if (proxy_auth && conn != NULL && conn->auth_user_request &&
            authenticateUserAuthenticated(conn->auth_user_request) &&
            conn->auth_user_request->connLastHeader() != NULL &&
            strcmp(proxy_auth, conn->auth_user_request->connLastHeader())) {
        debugs(29, 2, "authenticateAuthenticate: DUPLICATE AUTH - authentication header on already authenticated connection!. AU " <<
               conn->auth_user_request << ", Current user '" <<
               conn->auth_user_request->username() << "' proxy_auth " <<
               proxy_auth);

        /* remove this request struct - the link is already authed and it can't be to
         * reauth.
         */

        /* This should _only_ ever occur on the first pass through
         * authenticateAuthenticate
         */
        assert(*auth_user_request == NULL);
        AUTHUSERREQUESTUNLOCK(conn->auth_user_request, "conn");
        /* Set the connection auth type */
        conn->auth_type = AUTH_UNKNOWN;
    }

    /* we have a proxy auth header and as far as we know this connection has
     * not had bungled connection oriented authentication happen on it. */
    debugs(29, 9, "authenticateAuthenticate: header " << (proxy_auth ? proxy_auth : "-") << ".");

    if (*auth_user_request == NULL) {
        debugs(29, 9, "authenticateAuthenticate: This is a new checklist test on FD:" << (conn != NULL ? conn->fd : -1)  );

        if (proxy_auth && !request->auth_user_request && conn != NULL && conn->auth_user_request) {
            AuthConfig * scheme = AuthConfig::Find(proxy_auth);

            if (!conn->auth_user_request->user() || conn->auth_user_request->user()->config != scheme) {
                debugs(29, 1, "authenticateAuthenticate: Unexpected change of authentication scheme from '" <<
                       conn->auth_user_request->user()->config->type() <<
                       "' to '" << proxy_auth << "' (client " <<
                       src_addr << ")");

                AUTHUSERREQUESTUNLOCK(conn->auth_user_request, "conn");
                conn->auth_type = AUTH_UNKNOWN;
            }
        }

        if ((!request->auth_user_request)
                && (conn == NULL || conn->auth_type == AUTH_UNKNOWN)) {
            /* beginning of a new request check */
            debugs(29, 4, "authenticateAuthenticate: no connection authentication type");

            *auth_user_request = AuthConfig::CreateAuthUser(proxy_auth);
            if (!authenticateValidateUser(*auth_user_request)) {
                if (*auth_user_request == NULL)
                    return AUTH_ACL_CHALLENGE;

                /* the decode might have left a username for logging, or a message to
                 * the user */

                if ((*auth_user_request)->username()) {
                    request->auth_user_request = *auth_user_request;
                    AUTHUSERREQUESTLOCK(request->auth_user_request, "request");
                }

                *auth_user_request = NULL;
                return AUTH_ACL_CHALLENGE;
            }

            /* the user_request comes prelocked for the caller to createAuthUser (us) */
        } else if (request->auth_user_request) {
            *auth_user_request = request->auth_user_request;
        } else {
            assert (conn != NULL);
            if (conn->auth_user_request) {
                *auth_user_request = conn->auth_user_request;
            } else {
                /* failed connection based authentication */
                debugs(29, 4, "authenticateAuthenticate: Auth user request " <<
                       *auth_user_request << " conn-auth user request " <<
                       conn->auth_user_request << " conn type " <<
                       conn->auth_type << " authentication failed.");

                *auth_user_request = NULL;
                return AUTH_ACL_CHALLENGE;
            }
        }
    }

    if (!authenticateUserAuthenticated(*auth_user_request)) {
        /* User not logged in. Log them in */
        authenticateAuthenticateUser(*auth_user_request, request,
                                     conn, headertype);

        switch (authenticateDirection(*auth_user_request)) {

        case 1:

            if (NULL == request->auth_user_request) {
                request->auth_user_request = *auth_user_request;
                AUTHUSERREQUESTLOCK(request->auth_user_request, "request");
            }

            /* fallthrough to -2 */

        case -2:
            /* this ACL check is finished. */
            *auth_user_request = NULL;
            return AUTH_ACL_CHALLENGE;

        case -1:
            /* we are partway through authentication within squid,
             * the *auth_user_request variables stores the auth_user_request
             * for the callback to here - Do not Unlock */
            return AUTH_ACL_HELPER;
        }

        /* on 0 the authentication is finished - fallthrough */
        /* See if user authentication failed for some reason */
        if (!authenticateUserAuthenticated(*auth_user_request)) {
            if ((*auth_user_request)->username()) {
                if (!request->auth_user_request) {
                    request->auth_user_request = *auth_user_request;
                    AUTHUSERREQUESTLOCK(request->auth_user_request, "request");
                }
            }

            *auth_user_request = NULL;
            return AUTH_ACL_CHALLENGE;
        }
    }

    /* copy username to request for logging on client-side */
    /* the credentials are correct at this point */
    if (NULL == request->auth_user_request) {
        request->auth_user_request = *auth_user_request;
        AUTHUSERREQUESTLOCK(request->auth_user_request, "request");
        authenticateAuthUserRequestSetIp(*auth_user_request, src_addr);
    }

    return AUTH_AUTHENTICATED;
}