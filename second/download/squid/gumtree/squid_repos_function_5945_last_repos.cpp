void
Auth::Digest::UserRequest::authenticate(HttpRequest * request, ConnStateData *, Http::HdrType)
{
    HASHHEX SESSIONKEY;
    HASHHEX HA2 = "";
    HASHHEX Response;

    /* if the check has corrupted the user, just return */
    if (user() == NULL || user()->credentials() == Auth::Failed) {
        return;
    }

    Auth::User::Pointer auth_user = user();

    Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User*>(auth_user.getRaw());
    assert(digest_user != NULL);

    Auth::Digest::UserRequest *digest_request = this;

    /* do we have the HA1 */
    if (!digest_user->HA1created) {
        auth_user->credentials(Auth::Pending);
        return;
    }

    if (digest_request->nonce == NULL) {
        /* this isn't a nonce we issued */
        auth_user->credentials(Auth::Failed);
        return;
    }

    DigestCalcHA1(digest_request->algorithm, NULL, NULL, NULL,
                  authenticateDigestNonceNonceb64(digest_request->nonce),
                  digest_request->cnonce,
                  digest_user->HA1, SESSIONKEY);
    SBuf sTmp = request->method.image();
    DigestCalcResponse(SESSIONKEY, authenticateDigestNonceNonceb64(digest_request->nonce),
                       digest_request->nc, digest_request->cnonce, digest_request->qop,
                       sTmp.c_str(), digest_request->uri, HA2, Response);

    debugs(29, 9, "\nResponse = '" << digest_request->response << "'\nsquid is = '" << Response << "'");

    if (strcasecmp(digest_request->response, Response) != 0) {
        if (!digest_request->flags.helper_queried) {
            /* Query the helper in case the password has changed */
            digest_request->flags.helper_queried = true;
            auth_user->credentials(Auth::Pending);
            return;
        }

        if (static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->PostWorkaround && request->method != Http::METHOD_GET) {
            /* Ugly workaround for certain very broken browsers using the
             * wrong method to calculate the request-digest on POST request.
             * This should be deleted once Digest authentication becomes more
             * widespread and such broken browsers no longer are commonly
             * used.
             */
            sTmp = HttpRequestMethod(Http::METHOD_GET).image();
            DigestCalcResponse(SESSIONKEY, authenticateDigestNonceNonceb64(digest_request->nonce),
                               digest_request->nc, digest_request->cnonce, digest_request->qop,
                               sTmp.c_str(), digest_request->uri, HA2, Response);

            if (strcasecmp(digest_request->response, Response)) {
                auth_user->credentials(Auth::Failed);
                digest_request->flags.invalid_password = true;
                digest_request->setDenyMessage("Incorrect password");
                return;
            } else {
                const char *useragent = request->header.getStr(Http::HdrType::USER_AGENT);

                static Ip::Address last_broken_addr;
                static int seen_broken_client = 0;

                if (!seen_broken_client) {
                    last_broken_addr.setNoAddr();
                    seen_broken_client = 1;
                }

                if (last_broken_addr != request->client_addr) {
                    debugs(29, DBG_IMPORTANT, "Digest POST bug detected from " <<
                           request->client_addr << " using '" <<
                           (useragent ? useragent : "-") <<
                           "'. Please upgrade browser. See Bug #630 for details.");

                    last_broken_addr = request->client_addr;
                }
            }
        } else {
            auth_user->credentials(Auth::Failed);
            digest_request->flags.invalid_password = true;
            digest_request->setDenyMessage("Incorrect password");
            return;
        }
    }

    /* check for stale nonce */
    /* check Auth::Pending to avoid loop */

    if (!authDigestNonceIsValid(digest_request->nonce, digest_request->nc) && user()->credentials() != Auth::Pending) {
        debugs(29, 3, auth_user->username() << "' validated OK but nonce stale: " << digest_request->nonceb64);
        /* Pending prevent banner and makes a ldap control */
        auth_user->credentials(Auth::Pending);
        nonce->flags.valid = false;
        authDigestNoncePurge(nonce);
        return;
    }

    auth_user->credentials(Auth::Ok);

    /* password was checked and did match */
    debugs(29, 4, "user '" << auth_user->username() << "' validated OK");
}