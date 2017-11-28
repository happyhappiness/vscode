void
AuthDigestUserRequest::authenticate(HttpRequest * request, ConnStateData * conn, http_hdr_type type)
{
    AuthUser *auth_user;
    AuthDigestUserRequest *digest_request;
    digest_user_h *digest_user;

    HASHHEX SESSIONKEY;
    HASHHEX HA2 = "";
    HASHHEX Response;

    assert(authUser() != NULL);
    auth_user = authUser();

    digest_user = dynamic_cast < digest_user_h * >(auth_user);

    assert(digest_user != NULL);

    /* if the check has corrupted the user, just return */

    if (credentials() == Failed) {
        return;
    }

    digest_request = this;

    /* do we have the HA1 */

    if (!digest_user->HA1created) {
        credentials(Pending);
        return;
    }

    if (digest_request->nonce == NULL) {
        /* this isn't a nonce we issued */
        credentials(Failed);
        return;
    }

    DigestCalcHA1(digest_request->algorithm, NULL, NULL, NULL,
                  authenticateDigestNonceNonceb64(digest_request->nonce),
                  digest_request->cnonce,
                  digest_user->HA1, SESSIONKEY);
    DigestCalcResponse(SESSIONKEY, authenticateDigestNonceNonceb64(digest_request->nonce),
                       digest_request->nc, digest_request->cnonce, digest_request->qop,
                       RequestMethodStr(request->method), digest_request->uri, HA2, Response);

    debugs(29, 9, "\nResponse = '" << digest_request->response << "'\nsquid is = '" << Response << "'");

    if (strcasecmp(digest_request->response, Response) != 0) {
        if (!digest_request->flags.helper_queried) {
            /* Query the helper in case the password has changed */
            digest_request->flags.helper_queried = 1;
            digest_request->credentials_ok = Pending;
            return;
        }

        if (digestConfig.PostWorkaround && request->method != METHOD_GET) {
            /* Ugly workaround for certain very broken browsers using the
             * wrong method to calculate the request-digest on POST request.
             * This should be deleted once Digest authentication becomes more
             * widespread and such broken browsers no longer are commonly
             * used.
             */
            DigestCalcResponse(SESSIONKEY, authenticateDigestNonceNonceb64(digest_request->nonce),
                               digest_request->nc, digest_request->cnonce, digest_request->qop,
                               RequestMethodStr(METHOD_GET), digest_request->uri, HA2, Response);

            if (strcasecmp(digest_request->response, Response)) {
                credentials(Failed);
                digest_request->flags.invalid_password = 1;
                digest_request->setDenyMessage("Incorrect password");
                return;
            } else {
                const char *useragent = request->header.getStr(HDR_USER_AGENT);

                static IpAddress last_broken_addr;
                static int seen_broken_client = 0;

                if (!seen_broken_client) {
                    last_broken_addr.SetNoAddr();
                    seen_broken_client = 1;
                }

                if (last_broken_addr != request->client_addr) {
                    debugs(29, 1, "\nDigest POST bug detected from " <<
                           request->client_addr << " using '" <<
                           (useragent ? useragent : "-") <<
                           "'. Please upgrade browser. See Bug #630 for details.");

                    last_broken_addr = request->client_addr;
                }
            }
        } else {
            credentials(Failed);
            digest_request->flags.invalid_password = 1;
            digest_request->setDenyMessage("Incorrect password");
            return;
        }

        /* check for stale nonce */
        if (!authDigestNonceIsValid(digest_request->nonce, digest_request->nc)) {
            debugs(29, 3, "authenticateDigestAuthenticateuser: user '" << digest_user->username() << "' validated OK but nonce stale");
            credentials(Failed);
            digest_request->setDenyMessage("Stale nonce");
            return;
        }
    }

    credentials(Ok);

    /* password was checked and did match */
    debugs(29, 4, "authenticateDigestAuthenticateuser: user '" << digest_user->username() << "' validated OK");

    /* auth_user is now linked, we reset these values
     * after external auth occurs anyway */
    auth_user->expiretime = current_time.tv_sec;
    return;
}