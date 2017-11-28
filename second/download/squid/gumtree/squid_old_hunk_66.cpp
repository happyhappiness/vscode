
    /* the cache's link */
    authDigestNonceUnlink(nonce);
}

/* USER related functions */
static AuthUser *
authDigestUserFindUsername(const char *username)
{
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    debugs(29, 9, HERE << "Looking for user '" << username << "'");

    if (username && (usernamehash = static_cast < AuthUserHashPointer * >(hash_lookup(proxy_auth_username_cache, username)))) {
        while ((usernamehash->user()->auth_type != AUTH_DIGEST) &&
                (usernamehash->next))
            usernamehash = static_cast < AuthUserHashPointer * >(usernamehash->next);

        auth_user = NULL;

        if (usernamehash->user()->auth_type == AUTH_DIGEST) {
            auth_user = usernamehash->user();
        }

        return auth_user;
    }

    return NULL;
}

static void
authDigestUserShutdown(void)
{
    /** \todo Future work: the auth framework could flush it's cache */
    AuthUserHashPointer *usernamehash;
    AuthUser *auth_user;
    hash_first(proxy_auth_username_cache);

    while ((usernamehash = ((AuthUserHashPointer *) hash_next(proxy_auth_username_cache)))) {
        auth_user = usernamehash->user();

        if (strcmp(auth_user->config->type(), "digest") == 0)
            auth_user->unlock();
    }
}

/** delete the digest request structure. Does NOT delete related structures */
void
digestScheme::done()
{
    /** \todo this should be a Config call. */

    if (digestauthenticators)
        helperShutdown(digestauthenticators);

    if (DigestFieldsInfo) {
        httpHeaderDestroyFieldsInfo(DigestFieldsInfo, DIGEST_ENUM_END);
        DigestFieldsInfo = NULL;
    }

    authdigest_initialised = 0;

    if (!shutting_down) {
        authenticateDigestNonceReconfigure();
        return;
    }

    if (digestauthenticators) {
        helperFree(digestauthenticators);
        digestauthenticators = NULL;
    }

    authDigestUserShutdown();
    authenticateDigestNonceShutdown();
    debugs(29, 2, "authenticateDigestDone: Digest authentication shut down.");
}

void
AuthDigestConfig::dump(StoreEntry * entry, const char *name, AuthConfig * scheme)
{
    wordlist *list = authenticate;
    debugs(29, 9, "authDigestCfgDump: Dumping configuration");
    storeAppendPrintf(entry, "%s %s", name, "digest");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s %s realm %s\n%s %s children %d\n%s %s nonce_max_count %d\n%s %s nonce_max_duration %d seconds\n%s %s nonce_garbage_interval %d seconds\n",
                      name, "digest", digestAuthRealm,
                      name, "digest", authenticateChildren,
                      name, "digest", noncemaxuses,
                      name, "digest", (int) noncemaxduration,
                      name, "digest", (int) nonceGCInterval);
}

bool
AuthDigestConfig::active() const
{
    return authdigest_initialised == 1;
}

bool
AuthDigestConfig::configured() const
{
    if ((authenticate != NULL) &&
            (authenticateChildren != 0) &&
            (digestAuthRealm != NULL) && (noncemaxduration > -1))
        return true;

    return false;
}

int
AuthDigestUserRequest::authenticated() const
{
    if (credentials() == Ok)
        return 1;

    return 0;
}

/** log a digest user in
 */
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

int
AuthDigestUserRequest::module_direction()
{
    switch (credentials()) {

    case Unchecked:
        return -1;

    case Ok:

        return 0;

    case Pending:
        return -1;

    case Failed:

        /* send new challenge */
        return 1;
    }

    return -2;
}

/* add the [proxy]authorisation header */
void
AuthDigestUserRequest::addHeader(HttpReply * rep, int accel)
{
    http_hdr_type type;

    /* don't add to authentication error pages */

    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
        return;

    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;

#if WAITING_FOR_TE
    /* test for http/1.1 transfer chunked encoding */
    if (chunkedtest)
        return;

#endif

    if ((digestConfig.authenticate) && authDigestNonceLastRequest(nonce)) {
        flags.authinfo_sent = 1;
        debugs(29, 9, "authDigestAddHead: Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nonce) << "\"");
        httpHeaderPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nonce));
    }
}

#if WAITING_FOR_TE
/* add the [proxy]authorisation header */
void
AuthDigestUserRequest::addTrailer(HttpReply * rep, int accel)
{
    int type;

    if (!auth_user_request)
        return;


    /* has the header already been send? */
    if (flags.authinfo_sent)
        return;

    /* don't add to authentication error pages */
    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
        return;

    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;

    if ((digestConfig.authenticate) && authDigestNonceLastRequest(nonce)) {
        debugs(29, 9, "authDigestAddTrailer: Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nonce) << "\"");
        httpTrailerPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nonce));
    }
}

#endif

/* add the [www-|Proxy-]authenticate header on a 407 or 401 reply */
void
AuthDigestConfig::fixHeader(AuthUserRequest *auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (!authenticate)
        return;

    int stale = 0;

    if (auth_user_request) {
        AuthDigestUserRequest *digest_request;
        digest_request = dynamic_cast < AuthDigestUserRequest * >(auth_user_request);
        assert (digest_request != NULL);

        stale = !digest_request->flags.invalid_password;
    }

    /* on a 407 or 401 we always use a new nonce */
    digest_nonce_h *nonce = authenticateDigestNonceNew();

    debugs(29, 9, "authenticateFixHeader: Sending type:" << hdrType <<
           " header: 'Digest realm=\"" << digestAuthRealm << "\", nonce=\"" <<
           authenticateDigestNonceNonceb64(nonce) << "\", qop=\"" << QOP_AUTH <<
           "\", stale=" << (stale ? "true" : "false"));

    /* in the future, for WWW auth we may want to support the domain entry */
    httpHeaderPutStrf(&rep->header, hdrType, "Digest realm=\"%s\", nonce=\"%s\", qop=\"%s\", stale=%s", digestAuthRealm, authenticateDigestNonceNonceb64(nonce), QOP_AUTH, stale ? "true" : "false");
}

DigestUser::~DigestUser()
{

    dlink_node *link, *tmplink;
    link = nonces.head;

    while (link) {
        tmplink = link;
        link = link->next;
        dlinkDelete(tmplink, &nonces);
        authDigestNoncePurge(static_cast < digest_nonce_h * >(tmplink->data));
        authDigestNonceUnlink(static_cast < digest_nonce_h * >(tmplink->data));
        dlinkNodeDelete(tmplink);
    }
}

static void
authenticateDigestHandleReply(void *data, char *reply)
{
    DigestAuthenticateStateData *replyData = static_cast < DigestAuthenticateStateData * >(data);
    AuthUserRequest *auth_user_request;
    AuthDigestUserRequest *digest_request;
    digest_user_h *digest_user;
    char *t = NULL;
    void *cbdata;
    debugs(29, 9, "authenticateDigestHandleReply: {" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' ')))
            *t++ = '\0';

        if (*reply == '\0' || *reply == '\n')
            reply = NULL;
    }

    assert(replyData->auth_user_request != NULL);
    auth_user_request = replyData->auth_user_request;
    digest_request = dynamic_cast < AuthDigestUserRequest * >(auth_user_request);
    assert(digest_request);

    digest_user = dynamic_cast < digest_user_h * >(auth_user_request->user());
    assert(digest_user != NULL);

    if (reply && (strncasecmp(reply, "ERR", 3) == 0)) {
        digest_request->credentials(AuthDigestUserRequest::Failed);
        digest_request->flags.invalid_password = 1;

        if (t && *t)
            digest_request->setDenyMessage(t);
    } else if (reply) {
        CvtBin(reply, digest_user->HA1);
        digest_user->HA1created = 1;
    }

    if (cbdataReferenceValidDone(replyData->data, &cbdata))
        replyData->handler(cbdata, NULL);

    //we know replyData->auth_user_request != NULL, or we'd have asserted
    AUTHUSERREQUESTUNLOCK(replyData->auth_user_request, "replyData");

    cbdataFree(replyData);
}

/* Initialize helpers and the like for this auth scheme. Called AFTER parsing the
 * config file */
void
AuthDigestConfig::init(AuthConfig * scheme)
{
    if (authenticate) {
        DigestFieldsInfo = httpHeaderBuildFieldsInfo(DigestAttrs, DIGEST_ENUM_END);
        authenticateDigestNonceSetup();
        authdigest_initialised = 1;

        if (digestauthenticators == NULL)
            digestauthenticators = helperCreate("digestauthenticator");

        digestauthenticators->cmdline = authenticate;

        digestauthenticators->n_to_start = authenticateChildren;

        digestauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(digestauthenticators);

        CBDATA_INIT_TYPE(DigestAuthenticateStateData);
    }
}

void
AuthDigestConfig::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("digestauthenticator",
                   "Digest User Authenticator Stats",
                   authenticateDigestStats, 0, 1);
}

/* free any allocated configuration details */
void
AuthDigestConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);

    safe_free(digestAuthRealm);
}

AuthDigestConfig::AuthDigestConfig() :
        authenticateChildren(5),
        digestAuthRealm(NULL),
        authenticate(NULL),
        nonceGCInterval(5*60),
        noncemaxduration(30*60),
        noncemaxuses(50),
        NonceStrictness(0),
        CheckNonceCount(1),
        PostWorkaround(0),
        utf8(0)
{}

void
AuthDigestConfig::parse(AuthConfig * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticate)
            wordlistDestroy(&authenticate);

        parse_wordlist(&authenticate);

        requirePathnameExists("auth_param digest program", authenticate->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        parse_int(&authenticateChildren);
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&digestAuthRealm);
    } else if (strcasecmp(param_str, "nonce_garbage_interval") == 0) {
        parse_time_t(&nonceGCInterval);
    } else if (strcasecmp(param_str, "nonce_max_duration") == 0) {
        parse_time_t(&noncemaxduration);
