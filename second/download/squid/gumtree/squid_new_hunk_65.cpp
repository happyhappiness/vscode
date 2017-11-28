static void
authenticateBasicStats(StoreEntry * sentry)
{
    helperStats(sentry, basicauthenticators, "Basic Authenticator Statistics");
}

static Auth::User::Pointer
authBasicAuthUserFindUsername(const char *username)
{
    AuthUserHashPointer *usernamehash;
    debugs(29, 9, HERE << "Looking for user '" << username << "'");

    if (username && (usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, username)))) {
        while (usernamehash) {
            if ((usernamehash->user()->auth_type == Auth::AUTH_BASIC) &&
                    !strcmp(username, (char const *)usernamehash->key))
                return usernamehash->user();

            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
        }
    }

    return NULL;
}

char *
Auth::Basic::Config::decodeCleartext(const char *httpAuthHeader)
{
    const char *proxy_auth = httpAuthHeader;

    /* trim BASIC from string */
    while (xisgraph(*proxy_auth))
        proxy_auth++;

    /* Trim leading whitespace before decoding */
    while (xisspace(*proxy_auth))
        proxy_auth++;

    /* Trim trailing \n before decoding */
    // XXX: really? is the \n actually still there? does the header parse not drop it?
    char *eek = xstrdup(proxy_auth);
    strtok(eek, "\n");
    char *cleartext = uudecode(eek);
    safe_free(eek);

    if (cleartext) {
        /*
         * Don't allow NL or CR in the credentials.
         * Oezguer Kesim <oec@codeblau.de>
         */
        debugs(29, 9, HERE << "'" << cleartext << "'");

        if (strcspn(cleartext, "\r\n") != strlen(cleartext)) {
            debugs(29, DBG_IMPORTANT, "WARNING: Bad characters in authorization header '" << httpAuthHeader << "'");
            safe_free(cleartext);
        }
    }
    return cleartext;
}

/**
 * Decode a Basic [Proxy-]Auth string, linking the passed
 * auth_user_request structure to any existing user structure or creating one
 * if needed. Note that just returning will be treated as
 * "cannot decode credentials". Use the message field to return a
 * descriptive message to the user.
 */
Auth::UserRequest::Pointer
Auth::Basic::Config::decode(char const *proxy_auth)
{
    Auth::UserRequest::Pointer auth_user_request = dynamic_cast<Auth::UserRequest*>(new Auth::Basic::UserRequest);
    /* decode the username */

    // retrieve the cleartext (in a dynamically allocated char*)
    char *cleartext = decodeCleartext(proxy_auth);

    // empty header? no auth details produced...
    if (!cleartext)
        return auth_user_request;

    Auth::User::Pointer lb;
    /* permitted because local_basic is purely local function scope. */
    Auth::Basic::User *local_basic = NULL;

    char *seperator = strchr(cleartext, ':');

    lb = local_basic = new Auth::Basic::User(this);
    if (seperator == NULL) {
        local_basic->username(cleartext);
    } else {
        /* terminate the username */
        *seperator = '\0';
        local_basic->username(cleartext);
        local_basic->passwd = xstrdup(seperator+1);
    }

    if (!casesensitive)
        Tolower((char *)local_basic->username());

    if (local_basic->passwd == NULL) {
        debugs(29, 4, HERE << "no password in proxy authorization header '" << proxy_auth << "'");
        auth_user_request->setDenyMessage("no password was present in the HTTP [proxy-]authorization header. This is most likely a browser bug");
    } else {
        if (local_basic->passwd[0] == '\0') {
            debugs(29, 4, HERE << "Disallowing empty password. User is '" << local_basic->username() << "'");
            safe_free(local_basic->passwd);
            auth_user_request->setDenyMessage("Request denied because you provided an empty password. Users MUST have a password.");
        }
    }

    xfree(cleartext);

    if (!local_basic->valid()) {
        lb->auth_type = Auth::AUTH_BROKEN;
        auth_user_request->user(lb);
        return auth_user_request;
    }

    /* now lookup and see if we have a matching auth_user structure in memory. */
    Auth::User::Pointer auth_user;

    if ((auth_user = authBasicAuthUserFindUsername(lb->username())) == NULL) {
        /* the user doesn't exist in the username cache yet */
        /* save the credentials */
        debugs(29, 9, HERE << "Creating new user '" << lb->username() << "'");
        /* set the auth_user type */
        lb->auth_type = Auth::AUTH_BASIC;
        /* current time for timeouts */
        lb->expiretime = current_time.tv_sec;

        /* this basic_user struct is the 'lucky one' to get added to the username cache */
        /* the requests after this link to the basic_user */
        /* store user in hash */
        lb->addToNameCache();

        auth_user = lb;
        assert(auth_user != NULL);
    } else {
        /* replace the current cached password with the new one */
        Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(auth_user.getRaw());
        assert(basic_auth);
        basic_auth->updateCached(local_basic);
        auth_user = basic_auth;
    }

    /* link the request to the in-cache user */
    auth_user_request->user(auth_user);
    return auth_user_request;
}

/** Initialize helpers and the like for this auth scheme. Called AFTER parsing the
 * config file */
void
Auth::Basic::Config::init(Auth::Config * schemeCfg)
{
    if (authenticateProgram) {
        authbasic_initialised = 1;

        if (basicauthenticators == NULL)
            basicauthenticators = new helper("basicauthenticator");

        basicauthenticators->cmdline = authenticateProgram;

        basicauthenticators->childs.updateLimits(authenticateChildren);

        basicauthenticators->ipc_type = IPC_STREAM;

        helperOpenServers(basicauthenticators);
    }
}

void
Auth::Basic::Config::registerWithCacheManager(void)
{
    Mgr::RegisterAction("basicauthenticator",
                        "Basic User Authenticator Stats",
                        authenticateBasicStats, 0, 1);
}
