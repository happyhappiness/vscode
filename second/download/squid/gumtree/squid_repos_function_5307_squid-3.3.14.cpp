Auth::UserRequest::Pointer
Auth::Digest::Config::decode(char const *proxy_auth)
{
    const char *item;
    const char *p;
    const char *pos = NULL;
    char *username = NULL;
    digest_nonce_h *nonce;
    int ilen;

    debugs(29, 9, "authenticateDigestDecodeAuth: beginning");

    Auth::Digest::UserRequest *digest_request = new Auth::Digest::UserRequest();

    /* trim DIGEST from string */

    while (xisgraph(*proxy_auth))
        ++proxy_auth;

    /* Trim leading whitespace before decoding */
    while (xisspace(*proxy_auth))
        ++proxy_auth;

    String temp(proxy_auth);

    while (strListGetItem(&temp, ',', &item, &ilen, &pos)) {
        /* isolate directive name & value */
        size_t nlen;
        size_t vlen;
        if ((p = (const char *)memchr(item, '=', ilen)) && (p - item < ilen)) {
            nlen = p - item;
            ++p;
            vlen = ilen - (p - item);
        } else {
            nlen = ilen;
            vlen = 0;
        }

        StringArea keyName(item, nlen);
        String value;

        if (vlen > 0) {
            // see RFC 2617 section 3.2.1 and 3.2.2 for details on the BNF

            if (keyName == StringArea("domain",6) || keyName == StringArea("uri",3)) {
                // domain is Special. Not a quoted-string, must not be de-quoted. But is wrapped in '"'
                // BUG 3077: uri= can also be sent to us in a mangled (invalid!) form like domain
                if (*p == '"' && *(p + vlen -1) == '"') {
                    value.limitInit(p+1, vlen-2);
                }
            } else if (keyName == StringArea("qop",3)) {
                // qop is more special.
                // On request this must not be quoted-string de-quoted. But is several values wrapped in '"'
                // On response this is a single un-quoted token.
                if (*p == '"' && *(p + vlen -1) == '"') {
                    value.limitInit(p+1, vlen-2);
                } else {
                    value.limitInit(p, vlen);
                }
            } else if (*p == '"') {
                if (!httpHeaderParseQuotedString(p, vlen, &value)) {
                    debugs(29, 9, HERE << "Failed to parse attribute '" << item << "' in '" << temp << "'");
                    continue;
                }
            } else {
                value.limitInit(p, vlen);
            }
        } else {
            debugs(29, 9, HERE << "Failed to parse attribute '" << item << "' in '" << temp << "'");
            continue;
        }

        /* find type */
        http_digest_attr_type type = (http_digest_attr_type)httpHeaderIdByName(item, nlen, DigestFieldsInfo, DIGEST_ENUM_END);

        switch (type) {
        case DIGEST_USERNAME:
            safe_free(username);
            if (value.size() != 0)
                username = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found Username '" << username << "'");
            break;

        case DIGEST_REALM:
            safe_free(digest_request->realm);
            if (value.size() != 0)
                digest_request->realm = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found realm '" << digest_request->realm << "'");
            break;

        case DIGEST_QOP:
            safe_free(digest_request->qop);
            if (value.size() != 0)
                digest_request->qop = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found qop '" << digest_request->qop << "'");
            break;

        case DIGEST_ALGORITHM:
            safe_free(digest_request->algorithm);
            if (value.size() != 0)
                digest_request->algorithm = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found algorithm '" << digest_request->algorithm << "'");
            break;

        case DIGEST_URI:
            safe_free(digest_request->uri);
            if (value.size() != 0)
                digest_request->uri = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found uri '" << digest_request->uri << "'");
            break;

        case DIGEST_NONCE:
            safe_free(digest_request->nonceb64);
            if (value.size() != 0)
                digest_request->nonceb64 = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found nonce '" << digest_request->nonceb64 << "'");
            break;

        case DIGEST_NC:
            if (value.size() != 8) {
                debugs(29, 9, HERE << "Invalid nc '" << value << "' in '" << temp << "'");
            }
            xstrncpy(digest_request->nc, value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found noncecount '" << digest_request->nc << "'");
            break;

        case DIGEST_CNONCE:
            safe_free(digest_request->cnonce);
            if (value.size() != 0)
                digest_request->cnonce = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found cnonce '" << digest_request->cnonce << "'");
            break;

        case DIGEST_RESPONSE:
            safe_free(digest_request->response);
            if (value.size() != 0)
                digest_request->response = xstrndup(value.rawBuf(), value.size() + 1);
            debugs(29, 9, HERE << "Found response '" << digest_request->response << "'");
            break;

        default:
            debugs(29, 3, HERE << "Unknown attribute '" << item << "' in '" << temp << "'");
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

    // return value.
    Auth::UserRequest::Pointer rv;
    /* do we have a username ? */
    if (!username || username[0] == '\0') {
        debugs(29, 2, "Empty or not present username");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* Sanity check of the username.
     * " can not be allowed in usernames until * the digest helper protocol
     * have been redone
     */
    if (strchr(username, '"')) {
        debugs(29, 2, "Unacceptable username '" << username << "'");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* do we have a realm ? */
    if (!digest_request->realm || digest_request->realm[0] == '\0') {
        debugs(29, 2, "Empty or not present realm");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* and a nonce? */
    if (!digest_request->nonceb64 || digest_request->nonceb64[0] == '\0') {
        debugs(29, 2, "Empty or not present nonce");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* we can't check the URI just yet. We'll check it in the
     * authenticate phase, but needs to be given */
    if (!digest_request->uri || digest_request->uri[0] == '\0') {
        debugs(29, 2, "Missing URI field");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* is the response the correct length? */
    if (!digest_request->response || strlen(digest_request->response) != 32) {
        debugs(29, 2, "Response length invalid");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* check the algorithm is present and supported */
    if (!digest_request->algorithm)
        digest_request->algorithm = xstrndup("MD5", 4);
    else if (strcmp(digest_request->algorithm, "MD5")
             && strcmp(digest_request->algorithm, "MD5-sess")) {
        debugs(29, 2, "invalid algorithm specified!");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* 2617 requirements, indicated by qop */
    if (digest_request->qop) {

        /* check the qop is what we expected. */
        if (strcmp(digest_request->qop, QOP_AUTH) != 0) {
            /* we received a qop option we didn't send */
            debugs(29, 2, "Invalid qop option received");
            rv = authDigestLogUsername(username, digest_request);
            safe_free(username);
            return rv;
        }

        /* check cnonce */
        if (!digest_request->cnonce || digest_request->cnonce[0] == '\0') {
            debugs(29, 2, "Missing cnonce field");
            rv = authDigestLogUsername(username, digest_request);
            safe_free(username);
            return rv;
        }

        /* check nc */
        if (strlen(digest_request->nc) != 8 || strspn(digest_request->nc, "0123456789abcdefABCDEF") != 8) {
            debugs(29, 2, "invalid nonce count");
            rv = authDigestLogUsername(username, digest_request);
            safe_free(username);
            return rv;
        }
    } else {
        /* cnonce and nc both require qop */
        if (digest_request->cnonce || digest_request->nc[0] != '\0') {
            debugs(29, 2, "missing qop!");
            rv = authDigestLogUsername(username, digest_request);
            safe_free(username);
            return rv;
        }
    }

    /** below nonce state dependent **/

    /* now the nonce */
    nonce = authenticateDigestNonceFindNonce(digest_request->nonceb64);
    if (!nonce) {
        /* we couldn't find a matching nonce! */
        debugs(29, 2, "Unexpected or invalid nonce received");
        if (digest_request->user() != NULL)
            digest_request->user()->credentials(Auth::Failed);
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    digest_request->nonce = nonce;
    authDigestNonceLink(nonce);

    /* check that we're not being hacked / the username hasn't changed */
    if (nonce->user && strcmp(username, nonce->user->username())) {
        debugs(29, 2, "Username for the nonce does not equal the username for the request");
        rv = authDigestLogUsername(username, digest_request);
        safe_free(username);
        return rv;
    }

    /* the method we'll check at the authenticate step as well */

    /* we don't send or parse opaques. Ok so we're flexable ... */

    /* find the user */
    Auth::Digest::User *digest_user;

    Auth::User::Pointer auth_user;

    if ((auth_user = findUserInCache(username, Auth::AUTH_DIGEST)) == NULL) {
        /* the user doesn't exist in the username cache yet */
        debugs(29, 9, HERE << "Creating new digest user '" << username << "'");
        digest_user = new Auth::Digest::User(this);
        /* auth_user is a parent */
        auth_user = digest_user;
        /* save the username */
        digest_user->username(username);
        /* set the user type */
        digest_user->auth_type = Auth::AUTH_DIGEST;
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
        debugs(29, 9, HERE << "Found user '" << username << "' in the user cache as '" << auth_user << "'");
        digest_user = static_cast<Auth::Digest::User *>(auth_user.getRaw());
        digest_user->credentials(Auth::Unchecked);
        xfree(username);
    }

    /*link the request and the user */
    assert(digest_request != NULL);

    digest_request->user(digest_user);
    debugs(29, 9, HERE << "username = '" << digest_user->username() << "'\nrealm = '" <<
           digest_request->realm << "'\nqop = '" << digest_request->qop <<
           "'\nalgorithm = '" << digest_request->algorithm << "'\nuri = '" <<
           digest_request->uri << "'\nnonce = '" << digest_request->nonceb64 <<
           "'\nnc = '" << digest_request->nc << "'\ncnonce = '" <<
           digest_request->cnonce << "'\nresponse = '" <<
           digest_request->response << "'\ndigestnonce = '" << nonce << "'");

    return digest_request;
}