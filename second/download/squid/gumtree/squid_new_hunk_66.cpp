
    /* the cache's link */
    authDigestNonceUnlink(nonce);
}

/* USER related functions */
static Auth::User::Pointer
authDigestUserFindUsername(const char *username)
{
    AuthUserHashPointer *usernamehash;
    debugs(29, 9, HERE << "Looking for user '" << username << "'");

    if (username && (usernamehash = static_cast < AuthUserHashPointer * >(hash_lookup(proxy_auth_username_cache, username)))) {
        while ((usernamehash->user()->auth_type != Auth::AUTH_DIGEST) && (usernamehash->next))
            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);

        if (usernamehash->user()->auth_type == Auth::AUTH_DIGEST) {
            return usernamehash->user();
        }
    }

    return NULL;
}

void
Auth::Digest::Config::rotateHelpers()
{
    /* schedule closure of existing helpers */
    if (digestauthenticators) {
        helperShutdown(digestauthenticators);
    }

    /* NP: dynamic helper restart will ensure they start up again as needed. */
}

void
Auth::Digest::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme)
{
    wordlist *list = authenticateProgram;
    debugs(29, 9, "authDigestCfgDump: Dumping configuration");
    storeAppendPrintf(entry, "%s %s", name, "digest");

    while (list != NULL) {
        storeAppendPrintf(entry, " %s", list->key);
        list = list->next;
    }

    storeAppendPrintf(entry, "\n%s %s realm %s\n%s %s children %d startup=%d idle=%d concurrency=%d\n%s %s nonce_max_count %d\n%s %s nonce_max_duration %d seconds\n%s %s nonce_garbage_interval %d seconds\n",
                      name, "digest", digestAuthRealm,
                      name, "digest", authenticateChildren.n_max, authenticateChildren.n_startup, authenticateChildren.n_idle, authenticateChildren.concurrency,
                      name, "digest", noncemaxuses,
                      name, "digest", (int) noncemaxduration,
                      name, "digest", (int) nonceGCInterval);
}

bool
Auth::Digest::Config::active() const
{
    return authdigest_initialised == 1;
}

bool
Auth::Digest::Config::configured() const
{
    if ((authenticateProgram != NULL) &&
            (authenticateChildren.n_max != 0) &&
            (digestAuthRealm != NULL) && (noncemaxduration > -1))
        return true;

    return false;
}

/* add the [www-|Proxy-]authenticate header on a 407 or 401 reply */
void
Auth::Digest::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (!authenticateProgram)
        return;

    int stale = 0;

    if (auth_user_request != NULL) {
        Auth::Digest::UserRequest *digest_request = dynamic_cast<Auth::Digest::UserRequest*>(auth_user_request.getRaw());
        assert (digest_request != NULL);

        stale = !digest_request->flags.invalid_password;
    }

    /* on a 407 or 401 we always use a new nonce */
    digest_nonce_h *nonce = authenticateDigestNonceNew();

    debugs(29, 9, HERE << "Sending type:" << hdrType <<
           " header: 'Digest realm=\"" << digestAuthRealm << "\", nonce=\"" <<
           authenticateDigestNonceNonceb64(nonce) << "\", qop=\"" << QOP_AUTH <<
           "\", stale=" << (stale ? "true" : "false"));

    /* in the future, for WWW auth we may want to support the domain entry */
    httpHeaderPutStrf(&rep->header, hdrType, "Digest realm=\"%s\", nonce=\"%s\", qop=\"%s\", stale=%s", digestAuthRealm, authenticateDigestNonceNonceb64(nonce), QOP_AUTH, stale ? "true" : "false");
}

/* Initialize helpers and the like for this auth scheme. Called AFTER parsing the
 * config file */
void
Auth::Digest::Config::init(Auth::Config * scheme)
{
    if (authenticateProgram) {
        DigestFieldsInfo = httpHeaderBuildFieldsInfo(DigestAttrs, DIGEST_ENUM_END);
        authenticateDigestNonceSetup();
        authdigest_initialised = 1;

        if (digestauthenticators == NULL)
            digestauthenticators = new helper("digestauthenticator");

        digestauthenticators->cmdline = authenticateProgram;

        digestauthenticators->childs.updateLimits(authenticateChildren);

        digestauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(digestauthenticators);
    }
}

void
Auth::Digest::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("digestauthenticator",
                        "Digest User Authenticator Stats",
                        authenticateDigestStats, 0, 1);
}

/* free any allocated configuration details */
void
Auth::Digest::Config::done()
{
    authdigest_initialised = 0;

    if (digestauthenticators)
        helperShutdown(digestauthenticators);

    if (DigestFieldsInfo) {
        httpHeaderDestroyFieldsInfo(DigestFieldsInfo, DIGEST_ENUM_END);
        DigestFieldsInfo = NULL;
    }

    if (!shutting_down)
        return;

    delete digestauthenticators;
    digestauthenticators = NULL;

    if (authenticateProgram)
        wordlistDestroy(&authenticateProgram);

    safe_free(digestAuthRealm);
}

Auth::Digest::Config::Config() :
        digestAuthRealm(NULL),
        nonceGCInterval(5*60),
        noncemaxduration(30*60),
        noncemaxuses(50),
        NonceStrictness(0),
        CheckNonceCount(1),
        PostWorkaround(0),
        utf8(0)
{}

void
Auth::Digest::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcasecmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("auth_param digest program", authenticateProgram->key);
    } else if (strcasecmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();
    } else if (strcasecmp(param_str, "realm") == 0) {
        parse_eol(&digestAuthRealm);
    } else if (strcasecmp(param_str, "nonce_garbage_interval") == 0) {
        parse_time_t(&nonceGCInterval);
    } else if (strcasecmp(param_str, "nonce_max_duration") == 0) {
        parse_time_t(&noncemaxduration);
