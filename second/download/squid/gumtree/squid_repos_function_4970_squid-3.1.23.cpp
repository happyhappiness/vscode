AuthUserRequest *
AuthDigestConfig::decode(char const *proxy_auth)
{
    const char *item;
    const char *p;
    const char *pos = NULL;
    char *username = NULL;
    digest_nonce_h *nonce;
    int ilen;

    debugs(29, 9, "authenticateDigestDecodeAuth: beginning");

    AuthDigestUserRequest *digest_request = new AuthDigestUserRequest();

    /* trim DIGEST from string */

    while (xisgraph(*proxy_auth))
        proxy_auth++;

    /* Trim leading whitespace before decoding */
    while (xisspace(*proxy_auth))
        proxy_auth++;

    String temp(proxy_auth);

    while (strListGetItem(&temp, ',', &item, &ilen, &pos)) {
        /* isolate directive name & value */
        size_t nlen;
        size_t vlen;
        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen)) {
            nlen = p++ - item;
            vlen = ilen - (p - item);
        } else {
            nlen = ilen;
            vlen = 0;
        }

        String value;

        if (vlen > 0) {
            // see RFC 2617 section 3.2.1 and 3.2.2 for details on the BNF

            if ( (nlen == 6 && memcmp(item,"domain",6) == 0) || (nlen == 3 && memcmp(item,"uri",3) == 0) ) {
                // domain is Special. Not a quoted-string, must not be de-quoted. But is wrapped in '"'
                // BUG 3077: uri= can also be sent to us in a mangled (invalid!) form like domain
                if (*p == '"' && *(p + vlen-1) == '"') {
                    value.limitInit(p+1, vlen-2);
                } else {
                    value.limitInit(p, vlen);
                }
            } else if (nlen == 3 && memcmp(item,"qop",3) == 0) {
                // qop is more special.
                // On request this must not be quoted-string de-quoted. But is several values wrapped in '"'
                // On response this is a single un-quoted token.
                if (*p == '"' && *(p + vlen-1) == '"') {
                    value.limitInit(p+1, vlen-2);
                } else {
                    value.limitInit(p, vlen);
                }
            } else if (*p == '"') {
                if (!httpHeaderParseQuotedString(p, &value)) {
                    debugs(29, 9, "authDigestDecodeAuth: Failed to parse attribute '" << item << "' in '" << temp << "'");
                    continue;
                }
            } else {
                value.limitInit(p, vlen);
            }
        } else {
            debugs(29, 9, "authDigestDecodeAuth: Failed to parse attribute '" << item << "' in '" << temp << "'");
            continue;
        }

        /* find type */
        http_digest_attr_type type = (http_digest_attr_type)httpHeaderIdByName(item, nlen, DigestFieldsInfo, DIGEST_ENUM_END);

        switch (type) {
        case DIGEST_USERNAME:
            safe_free(username);
            username = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found Username '" << username << "'");
            break;

        case DIGEST_REALM:
            safe_free(digest_request->realm);
            digest_request->realm = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found realm '" << digest_request->realm << "'");
            break;

        case DIGEST_QOP:
            safe_free(digest_request->qop);
            digest_request->qop = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found qop '" << digest_request->qop << "'");
            break;

        case DIGEST_ALGORITHM:
            safe_free(digest_request->algorithm);
            digest_request->algorithm = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found algorithm '" << digest_request->algorithm << "'");
            break;

        case DIGEST_URI:
            safe_free(digest_request->uri);
            digest_request->uri = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found uri '" << digest_request->uri << "'");
            break;

        case DIGEST_NONCE:
            safe_free(digest_request->nonceb64);
            digest_request->nonceb64 = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found nonce '" << digest_request->nonceb64 << "'");
            break;

        case DIGEST_NC:
            if (value.size() != 8) {
                debugs(29, 9, "authDigestDecodeAuth: Invalid nc '" << value << "' in '" << temp << "'");
            }
            xstrncpy(digest_request->nc, value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found noncecount '" << digest_request->nc << "'");
            break;

        case DIGEST_CNONCE:
            safe_free(digest_request->cnonce);
            digest_request->cnonce = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found cnonce '" << digest_request->cnonce << "'");
            break;

        case DIGEST_RESPONSE:
            safe_free(digest_request->response);
            digest_request->response = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, "authDigestDecodeAuth: Found response '" << digest_request->response << "'");
            break;

        default:
            debugs(29, 3, "authDigestDecodeAuth: Unknown attribute '" << item << "' in '" << temp << "'");
            break;
        }
    }

    temp.clean();


    /* now we validate the data given to us */

    /*
     * TODO: on invalid parameters we should return 400, not 407.
     * Find some clean way of doing this. perhaps return a valid
     * struct, and set the direction to clientwards combined with
     * a change to the clientwards handling code (ie let the
     * clientwards call set the error type (but limited to known
     * correct values - 400/401/407
     */

    /* 2069 requirements */

    /* do we have a username ? */
    if (!username || username[0] == '\0') {
        debugs(29, 2, "authenticateDigestDecode: Empty or not present username");
        return authDigestLogUsername(username, digest_request);
    }

    /* Sanity check of the username.
     * " can not be allowed in usernames until * the digest helper protocol
     * have been redone
     */
    if (strchr(username, '"')) {
        debugs(29, 2, "authenticateDigestDecode: Unacceptable username '" << username << "'");
        return authDigestLogUsername(username, digest_request);
    }

    /* do we have a realm ? */
    if (!digest_request->realm || digest_request->realm[0] == '\0') {
        debugs(29, 2, "authenticateDigestDecode: Empty or not present realm");
        return authDigestLogUsername(username, digest_request);
    }

    /* and a nonce? */
    if (!digest_request->nonceb64 || digest_request->nonceb64[0] == '\0') {
        debugs(29, 2, "authenticateDigestDecode: Empty or not present nonce");
        return authDigestLogUsername(username, digest_request);
    }

    /* we can't check the URI just yet. We'll check it in the
     * authenticate phase, but needs to be given */
    if (!digest_request->uri || digest_request->uri[0] == '\0') {
        debugs(29, 2, "authenticateDigestDecode: Missing URI field");
        return authDigestLogUsername(username, digest_request);
    }

    /* is the response the correct length? */
    if (!digest_request->response || strlen(digest_request->response) != 32) {
        debugs(29, 2, "authenticateDigestDecode: Response length invalid");
        return authDigestLogUsername(username, digest_request);
    }

    /* check the algorithm is present and supported */
    if (!digest_request->algorithm)
        digest_request->algorithm = xstrndup("MD5", 4);
    else if (strcmp(digest_request->algorithm, "MD5")
             && strcmp(digest_request->algorithm, "MD5-sess")) {
        debugs(29, 2, "authenticateDigestDecode: invalid algorithm specified!");
        return authDigestLogUsername(username, digest_request);
    }

    /* 2617 requirements, indicated by qop */
    if (digest_request->qop) {

        /* check the qop is what we expected. */
        if (strcmp(digest_request->qop, QOP_AUTH) != 0) {
            /* we received a qop option we didn't send */
            debugs(29, 2, "authenticateDigestDecode: Invalid qop option received");
            return authDigestLogUsername(username, digest_request);
        }

        /* check cnonce */
        if (!digest_request->cnonce || digest_request->cnonce[0] == '\0') {
            debugs(29, 2, "authenticateDigestDecode: Missing cnonce field");
            return authDigestLogUsername(username, digest_request);
        }

        /* check nc */
        if (strlen(digest_request->nc) != 8 || strspn(digest_request->nc, "0123456789abcdefABCDEF") != 8) {
            debugs(29, 2, "authenticateDigestDecode: invalid nonce count");
            return authDigestLogUsername(username, digest_request);
        }
    } else {
        /* cnonce and nc both require qop */
        if (digest_request->cnonce || digest_request->nc) {
            debugs(29, 2, "authenticateDigestDecode: missing qop!");
            return authDigestLogUsername(username, digest_request);
        }
    }

    /** below nonce state dependent **/

    /* now the nonce */
    nonce = authenticateDigestNonceFindNonce(digest_request->nonceb64);
    if (!nonce) {
        /* we couldn't find a matching nonce! */
        debugs(29, 2, "authenticateDigestDecode: Unexpected or invalid nonce received");
        digest_request->credentials(AuthDigestUserRequest::Failed);
        return authDigestLogUsername(username, digest_request);
    }

    digest_request->nonce = nonce;
    authDigestNonceLink(nonce);

    /* check that we're not being hacked / the username hasn't changed */
    if (nonce->user && strcmp(username, nonce->user->username())) {
        debugs(29, 2, "authenticateDigestDecode: Username for the nonce does not equal the username for the request");
        return authDigestLogUsername(username, digest_request);
    }

    /* the method we'll check at the authenticate step as well */


    /* we don't send or parse opaques. Ok so we're flexable ... */

    /* find the user */
    digest_user_h *digest_user;

    AuthUser *auth_user;

    if ((auth_user = authDigestUserFindUsername(username)) == NULL) {
        /* the user doesn't exist in the username cache yet */
        debugs(29, 9, "authDigestDecodeAuth: Creating new digest user '" << username << "'");
        digest_user = new DigestUser (&digestConfig);
        /* auth_user is a parent */
        auth_user = digest_user;
        /* save the username */
        digest_user->username(username);
        /* set the user type */
        digest_user->auth_type = AUTH_DIGEST;
        /* this auth_user struct is the one to get added to the
         * username cache */
        /* store user in hash's */
        digest_user->addToNameCache();

        /*
         * Add the digest to the user so we can tell if a hacking
         * or spoofing attack is taking place. We do this by assuming
         * the user agent won't change user name without warning.
         */
        authDigestUserLinkNonce(digest_user, nonce);
    } else {
        debugs(29, 9, "authDigestDecodeAuth: Found user '" << username << "' in the user cache as '" << auth_user << "'");
        digest_user = static_cast < digest_user_h * >(auth_user);
        xfree(username);
    }

    /*link the request and the user */
    assert(digest_request != NULL);

    digest_request->user(digest_user);

    digest_user->addRequest (digest_request);

    debugs(29, 9, "username = '" << digest_user->username() << "'\nrealm = '" <<
           digest_request->realm << "'\nqop = '" << digest_request->qop <<
           "'\nalgorithm = '" << digest_request->algorithm << "'\nuri = '" <<
           digest_request->uri << "'\nnonce = '" << digest_request->nonceb64 <<
           "'\nnc = '" << digest_request->nc << "'\ncnonce = '" <<
           digest_request->cnonce << "'\nresponse = '" <<
           digest_request->response << "'\ndigestnonce = '" << nonce << "'");

    return digest_request;
}