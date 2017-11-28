AuthAclState
Auth::UserRequest::authenticate(Auth::UserRequest::Pointer * auth_user_request, http_hdr_type headertype, HttpRequest * request, ConnStateData * conn, Ip::Address &src_addr)
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

    /* a) can we find other credentials to use? and b) are they logged in already? */
    if (proxy_auth == NULL && !authenticateUserAuthenticated(authTryGetUser(*auth_user_request,conn,request))) {
        /* no header or authentication failed/got corrupted - restart */
        debugs(29, 4, HERE << "No Proxy-Auth header and no working alternative. Requesting auth header.");

        /* something wrong with the AUTH credentials. Force a new attempt */

        /* connection auth we must reset on auth errors */
        if (conn != NULL) {
            conn->setAuth(NULL, "HTTP request missing credentials");
        }

        *auth_user_request = NULL;
        return AUTH_ACL_CHALLENGE;
    }

    /*
     * Is this an already authenticated connection with a new auth header?
     * No check for function required in the if: its compulsory for conn based
     * auth modules
     */
    if (proxy_auth && conn != NULL && conn->getAuth() != NULL &&
            authenticateUserAuthenticated(conn->getAuth()) &&
            conn->getAuth()->connLastHeader() != NULL &&
            strcmp(proxy_auth, conn->getAuth()->connLastHeader())) {
        debugs(29, 2, "WARNING: DUPLICATE AUTH - authentication header on already authenticated connection!. AU " <<
               conn->getAuth() << ", Current user '" <<
               conn->getAuth()->username() << "' proxy_auth " <<
               proxy_auth);

        /* remove this request struct - the link is already authed and it can't be to reauth. */

        /* This should _only_ ever occur on the first pass through
         * authenticateAuthenticate
         */
        assert(*auth_user_request == NULL);
        conn->setAuth(NULL, "changed credentials token");
    }

    /* we have a proxy auth header and as far as we know this connection has
     * not had bungled connection oriented authentication happen on it. */
    debugs(29, 9, HERE << "header " << (proxy_auth ? proxy_auth : "-") << ".");

    if (*auth_user_request == NULL) {
        if (conn != NULL) {
            debugs(29, 9, HERE << "This is a new checklist test on:" << conn->clientConnection);
        }

        if (proxy_auth && request->auth_user_request == NULL && conn != NULL && conn->getAuth() != NULL) {
            Auth::Config * scheme = Auth::Config::Find(proxy_auth);

            if (conn->getAuth()->user() == NULL || conn->getAuth()->user()->config != scheme) {
                debugs(29, DBG_IMPORTANT, "WARNING: Unexpected change of authentication scheme from '" <<
                       (conn->getAuth()->user()!=NULL?conn->getAuth()->user()->config->type():"[no user]") <<
                       "' to '" << proxy_auth << "' (client " <<
                       src_addr << ")");

                conn->setAuth(NULL, "changed auth scheme");
            }
        }

        if (request->auth_user_request == NULL && (conn == NULL || conn->getAuth() == NULL)) {
            /* beginning of a new request check */
            debugs(29, 4, HERE << "No connection authentication type");

            *auth_user_request = Auth::Config::CreateAuthUser(proxy_auth);
            if (*auth_user_request == NULL)
                return AUTH_ACL_CHALLENGE;
            else if (!(*auth_user_request)->valid()) {
                /* the decode might have left a username for logging, or a message to
                 * the user */

                if ((*auth_user_request)->username()) {
                    request->auth_user_request = *auth_user_request;
                }

                *auth_user_request = NULL;
                return AUTH_ACL_CHALLENGE;
            }

        } else if (request->auth_user_request != NULL) {
            *auth_user_request = request->auth_user_request;
        } else {
            assert (conn != NULL);
            if (conn->getAuth() != NULL) {
                *auth_user_request = conn->getAuth();
            } else {
                /* failed connection based authentication */
                debugs(29, 4, HERE << "Auth user request " << *auth_user_request << " conn-auth missing and failed to authenticate.");
                *auth_user_request = NULL;
                return AUTH_ACL_CHALLENGE;
            }
        }
    }

    if (!authenticateUserAuthenticated(*auth_user_request)) {
        /* User not logged in. Try to log them in */
        authenticateAuthenticateUser(*auth_user_request, request, conn, headertype);

        switch ((*auth_user_request)->direction()) {

        case Auth::CRED_CHALLENGE:

            if (request->auth_user_request == NULL) {
                request->auth_user_request = *auth_user_request;
            }

            /* fallthrough to ERROR case and do the challenge */

        case Auth::CRED_ERROR:
            /* this ACL check is finished. */
            *auth_user_request = NULL;
            return AUTH_ACL_CHALLENGE;

        case Auth::CRED_LOOKUP:
            /* we are partway through authentication within squid,
             * the *auth_user_request variables stores the auth_user_request
             * for the callback to here - Do not Unlock */
            return AUTH_ACL_HELPER;

        case Auth::CRED_VALID:
            /* authentication is finished */
            /* See if user authentication failed for some reason */
            if (!authenticateUserAuthenticated(*auth_user_request)) {
                if ((*auth_user_request)->username()) {
                    if (!request->auth_user_request) {
                        request->auth_user_request = *auth_user_request;
                    }
                }

                *auth_user_request = NULL;
                return AUTH_ACL_CHALLENGE;
            }
            // otherwise fallthrough to acceptance.
        }
    }

    /* copy username to request for logging on client-side */
    /* the credentials are correct at this point */
    if (request->auth_user_request == NULL) {
        request->auth_user_request = *auth_user_request;
        authenticateAuthUserRequestSetIp(*auth_user_request, src_addr);
    }

    return AUTH_AUTHENTICATED;
}