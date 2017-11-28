 static void
 authenticateBasicStats(StoreEntry * sentry)
 {
     helperStats(sentry, basicauthenticators, "Basic Authenticator Statistics");
 }
 
-CBDATA_TYPE(AuthenticateStateData);
-
-static AuthUser *
+static Auth::User::Pointer
 authBasicAuthUserFindUsername(const char *username)
 {
     AuthUserHashPointer *usernamehash;
     debugs(29, 9, HERE << "Looking for user '" << username << "'");
 
     if (username && (usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, username)))) {
         while (usernamehash) {
-            if ((usernamehash->user()->auth_type == AUTH_BASIC) &&
+            if ((usernamehash->user()->auth_type == Auth::AUTH_BASIC) &&
                     !strcmp(username, (char const *)usernamehash->key))
                 return usernamehash->user();
 
             usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
         }
     }
 
     return NULL;
 }
 
-void
-BasicUser::deleteSelf() const
-{
-    delete this;
-}
-
-BasicUser::BasicUser(AuthConfig *aConfig) : AuthUser (aConfig) , passwd (NULL), credentials_checkedtime(0), auth_queue(NULL), cleartext (NULL), currentRequest (NULL), httpAuthHeader (NULL)
+char *
+Auth::Basic::Config::decodeCleartext(const char *httpAuthHeader)
 {
-    flags.credentials_ok = 0;
-}
+    const char *proxy_auth = httpAuthHeader;
 
-bool
-BasicUser::decodeCleartext()
-{
-    char *sent_auth = NULL;
+    /* trim BASIC from string */
+    while (xisgraph(*proxy_auth))
+        proxy_auth++;
 
-    /* username and password */
-    sent_auth = xstrdup(httpAuthHeader);
+    /* Trim leading whitespace before decoding */
+    while (xisspace(*proxy_auth))
+        proxy_auth++;
 
     /* Trim trailing \n before decoding */
-    strtok(sent_auth, "\n");
+    // XXX: really? is the \n actually still there? does the header parse not drop it?
+    char *eek = xstrdup(proxy_auth);
+    strtok(eek, "\n");
+    char *cleartext = uudecode(eek);
+    safe_free(eek);
+
+    if (cleartext) {
+        /*
+         * Don't allow NL or CR in the credentials.
+         * Oezguer Kesim <oec@codeblau.de>
+         */
+        debugs(29, 9, HERE << "'" << cleartext << "'");
+
+        if (strcspn(cleartext, "\r\n") != strlen(cleartext)) {
+            debugs(29, DBG_IMPORTANT, "WARNING: Bad characters in authorization header '" << httpAuthHeader << "'");
+            safe_free(cleartext);
+        }
+    }
+    return cleartext;
+}
 
-    cleartext = uudecode(sent_auth);
+/**
+ * Decode a Basic [Proxy-]Auth string, linking the passed
+ * auth_user_request structure to any existing user structure or creating one
+ * if needed. Note that just returning will be treated as
+ * "cannot decode credentials". Use the message field to return a
+ * descriptive message to the user.
+ */
+Auth::UserRequest::Pointer
+Auth::Basic::Config::decode(char const *proxy_auth)
+{
+    Auth::UserRequest::Pointer auth_user_request = dynamic_cast<Auth::UserRequest*>(new Auth::Basic::UserRequest);
+    /* decode the username */
 
-    safe_free(sent_auth);
+    // retrieve the cleartext (in a dynamically allocated char*)
+    char *cleartext = decodeCleartext(proxy_auth);
 
+    // empty header? no auth details produced...
     if (!cleartext)
-        return false;
+        return auth_user_request;
 
-    /*
-     * Don't allow NL or CR in the credentials.
-     * Oezguer Kesim <oec@codeblau.de>
-     */
-    debugs(29, 9, HERE << "'" << cleartext << "'");
-
-    if (strcspn(cleartext, "\r\n") != strlen(cleartext)) {
-        debugs(29, 1, HERE << "bad characters in authorization header '" << httpAuthHeader << "'");
-        safe_free(cleartext);
-        return false;
-    }
-    return true;
-}
+    Auth::User::Pointer lb;
+    /* permitted because local_basic is purely local function scope. */
+    Auth::Basic::User *local_basic = NULL;
 
-void
-BasicUser::extractUsername()
-{
-    char * seperator = strchr(cleartext, ':');
+    char *seperator = strchr(cleartext, ':');
 
+    lb = local_basic = new Auth::Basic::User(this);
     if (seperator == NULL) {
-        username(cleartext);
+        local_basic->username(cleartext);
     } else {
         /* terminate the username */
         *seperator = '\0';
-
-        username(cleartext);
-
-        /* replace the colon so we can find the password */
-        *seperator = ':';
+        local_basic->username(cleartext);
+        local_basic->passwd = xstrdup(seperator+1);
     }
 
-    if (!basicConfig.casesensitive)
-        Tolower((char *)username());
-}
-
-void
-BasicUser::extractPassword()
-{
-    passwd = strchr(cleartext, ':');
+    if (!casesensitive)
+        Tolower((char *)local_basic->username());
 
-    if (passwd == NULL) {
-        debugs(29, 4, HERE << "no password in proxy authorization header '" << httpAuthHeader << "'");
-        passwd = NULL;
-        currentRequest->setDenyMessage("no password was present in the HTTP [proxy-]authorization header. This is most likely a browser bug");
+    if (local_basic->passwd == NULL) {
+        debugs(29, 4, HERE << "no password in proxy authorization header '" << proxy_auth << "'");
+        auth_user_request->setDenyMessage("no password was present in the HTTP [proxy-]authorization header. This is most likely a browser bug");
     } else {
-        ++passwd;
-        if (*passwd == '\0') {
-            debugs(29, 4, HERE << "Disallowing empty password,user is '" << username() << "'");
-            passwd = NULL;
-            currentRequest->setDenyMessage("Request denied because you provided an empty password. Users MUST have a password.");
-        } else {
-            passwd = xstrndup(passwd, USER_IDENT_SZ);
+        if (local_basic->passwd[0] == '\0') {
+            debugs(29, 4, HERE << "Disallowing empty password. User is '" << local_basic->username() << "'");
+            safe_free(local_basic->passwd);
+            auth_user_request->setDenyMessage("Request denied because you provided an empty password. Users MUST have a password.");
         }
     }
-}
-
-void
-BasicUser::decode(char const *proxy_auth, AuthUserRequest *auth_user_request)
-{
-    currentRequest = auth_user_request;
-    httpAuthHeader = proxy_auth;
-    if (decodeCleartext ()) {
-        extractUsername();
-        extractPassword();
-    }
-    currentRequest = NULL;
-    httpAuthHeader = NULL;
-}
-
-bool
-BasicUser::valid() const
-{
-    if (username() == NULL)
-        return false;
-    if (passwd == NULL)
-        return false;
-    return true;
-}
-
-void
-BasicUser::makeLoggingInstance(AuthBasicUserRequest *auth_user_request)
-{
-    if (username()) {
-        /* log the username */
-        debugs(29, 9, HERE << "Creating new user for logging '" << username() << "'");
-        /* new scheme data */
-        BasicUser *basic_auth = new BasicUser(& basicConfig);
-        auth_user_request->user(basic_auth);
-        /* save the credentials */
-        basic_auth->username(username());
-        username(NULL);
-        /* set the auth_user type */
-        basic_auth->auth_type = AUTH_BROKEN;
-        /* link the request to the user */
-        basic_auth->addRequest(auth_user_request);
-    }
-}
-
-AuthUser *
-BasicUser::makeCachedFrom()
-{
-    /* the user doesn't exist in the username cache yet */
-    debugs(29, 9, HERE << "Creating new user '" << username() << "'");
-    BasicUser *basic_user = new BasicUser(&basicConfig);
-    /* save the credentials */
-    basic_user->username(username());
-    username(NULL);
-    basic_user->passwd = passwd;
-    passwd = NULL;
-    /* set the auth_user type */
-    basic_user->auth_type = AUTH_BASIC;
-    /* current time for timeouts */
-    basic_user->expiretime = current_time.tv_sec;
-
-    /* this basic_user struct is the 'lucky one' to get added to the username cache */
-    /* the requests after this link to the basic_user */
-    /* store user in hash */
-    basic_user->addToNameCache();
-    return basic_user;
-}
-
-void
-BasicUser::updateCached(BasicUser *from)
-{
-    debugs(29, 9, HERE << "Found user '" << from->username() << "' in the user cache as '" << this << "'");
-
-    if (strcmp(from->passwd, passwd)) {
-        debugs(29, 4, HERE << "new password found. Updating in user master record and resetting auth state to unchecked");
-        flags.credentials_ok = 0;
-        xfree(passwd);
-        passwd = from->passwd;
-        from->passwd = NULL;
-    }
-
-    if (flags.credentials_ok == 3) {
-        debugs(29, 4, HERE << "last attempt to authenticate this user failed, resetting auth state to unchecked");
-        flags.credentials_ok = 0;
-    }
-}
 
-/**
- * Decode a Basic [Proxy-]Auth string, linking the passed
- * auth_user_request structure to any existing user structure or creating one
- * if needed. Note that just returning will be treated as
- * "cannot decode credentials". Use the message field to return a
- * descriptive message to the user.
- */
-AuthUserRequest *
-AuthBasicConfig::decode(char const *proxy_auth)
-{
-    AuthBasicUserRequest *auth_user_request = new AuthBasicUserRequest();
-    /* decode the username */
-    /* trim BASIC from string */
+    xfree(cleartext);
 
-    while (xisgraph(*proxy_auth))
-        proxy_auth++;
-
-    BasicUser *basic_auth, local_basic(&basicConfig);
-
-    /* Trim leading whitespace before decoding */
-    while (xisspace(*proxy_auth))
-        proxy_auth++;
-
-    local_basic.decode(proxy_auth, auth_user_request);
-
-    if (!local_basic.valid()) {
-        local_basic.makeLoggingInstance(auth_user_request);
+    if (!local_basic->valid()) {
+        lb->auth_type = Auth::AUTH_BROKEN;
+        auth_user_request->user(lb);
         return auth_user_request;
     }
 
-    /* now lookup and see if we have a matching auth_user structure in
-     * memory. */
+    /* now lookup and see if we have a matching auth_user structure in memory. */
+    Auth::User::Pointer auth_user;
 
-    AuthUser *auth_user;
+    if ((auth_user = authBasicAuthUserFindUsername(lb->username())) == NULL) {
+        /* the user doesn't exist in the username cache yet */
+        /* save the credentials */
+        debugs(29, 9, HERE << "Creating new user '" << lb->username() << "'");
+        /* set the auth_user type */
+        lb->auth_type = Auth::AUTH_BASIC;
+        /* current time for timeouts */
+        lb->expiretime = current_time.tv_sec;
+
+        /* this basic_user struct is the 'lucky one' to get added to the username cache */
+        /* the requests after this link to the basic_user */
+        /* store user in hash */
+        lb->addToNameCache();
 
-    if ((auth_user = authBasicAuthUserFindUsername(local_basic.username())) == NULL) {
-        auth_user = local_basic.makeCachedFrom();
-        basic_auth = dynamic_cast<BasicUser *>(auth_user);
-        assert (basic_auth);
+        auth_user = lb;
+        assert(auth_user != NULL);
     } else {
-        basic_auth = dynamic_cast<BasicUser *>(auth_user);
-        assert (basic_auth);
-        basic_auth->updateCached (&local_basic);
+        /* replace the current cached password with the new one */
+        Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(auth_user.getRaw());
+        assert(basic_auth);
+        basic_auth->updateCached(local_basic);
+        auth_user = basic_auth;
     }
 
     /* link the request to the in-cache user */
-    auth_user_request->user(basic_auth);
-
-    basic_auth->addRequest(auth_user_request);
-
+    auth_user_request->user(auth_user);
     return auth_user_request;
 }
 
 /** Initialize helpers and the like for this auth scheme. Called AFTER parsing the
  * config file */
 void
-AuthBasicConfig::init(AuthConfig * scheme)
+Auth::Basic::Config::init(Auth::Config * schemeCfg)
 {
-    if (authenticate) {
+    if (authenticateProgram) {
         authbasic_initialised = 1;
 
         if (basicauthenticators == NULL)
-            basicauthenticators = helperCreate("basicauthenticator");
+            basicauthenticators = new helper("basicauthenticator");
 
-        basicauthenticators->cmdline = authenticate;
+        basicauthenticators->cmdline = authenticateProgram;
 
-        basicauthenticators->n_to_start = authenticateChildren;
-
-        basicauthenticators->concurrency = authenticateConcurrency;
+        basicauthenticators->childs.updateLimits(authenticateChildren);
 
         basicauthenticators->ipc_type = IPC_STREAM;
 
         helperOpenServers(basicauthenticators);
-
-        CBDATA_INIT_TYPE(AuthenticateStateData);
-    }
-}
-
-void
-AuthBasicConfig::registerWithCacheManager(void)
-{
-    CacheManager::GetInstance()->
-    registerAction("basicauthenticator",
-                   "Basic User Authenticator Stats",
-                   authenticateBasicStats, 0, 1);
-}
-
-void
-BasicUser::queueRequest(AuthUserRequest * auth_user_request, RH * handler, void *data)
-{
-    BasicAuthQueueNode *node;
-    node = static_cast<BasicAuthQueueNode *>(xmalloc(sizeof(BasicAuthQueueNode)));
-    assert(node);
-    /* save the details */
-    node->next = auth_queue;
-    auth_queue = node;
-    node->auth_user_request = auth_user_request;
-    node->handler = handler;
-    node->data = cbdataReference(data);
-}
-
-/* send the initial data to a basic authenticator module */
-void
-AuthBasicUserRequest::module_start(RH * handler, void *data)
-{
-    basic_data *basic_auth;
-    assert(user()->auth_type == AUTH_BASIC);
-    basic_auth = dynamic_cast<basic_data *>(user());
-    assert(basic_auth != NULL);
-    debugs(29, 9, HERE << "'" << basic_auth->username() << ":" << basic_auth->passwd << "'");
-
-    if (basicConfig.authenticate == NULL) {
-        handler(data, NULL);
-        return;
-    }
-
-    /* check to see if the auth_user already has a request outstanding */
-    if (basic_auth->flags.credentials_ok == 2) {
-        /* there is a request with the same credentials already being verified */
-        basic_auth->queueRequest(this, handler, data);
-        return;
     }
-
-    basic_auth->submitRequest (this, handler, data);
 }
 
 void
-BasicUser::submitRequest(AuthUserRequest * auth_user_request, RH * handler, void *data)
-{
-    /* mark the user as haveing verification in progress */
-    flags.credentials_ok = 2;
-    AuthenticateStateData *r = NULL;
-    char buf[8192];
-    char user[1024], pass[1024];
-    r = cbdataAlloc(AuthenticateStateData);
-    r->handler = handler;
-    r->data = cbdataReference(data);
-    r->auth_user_request = auth_user_request;
-    if (basicConfig.utf8) {
-        latin1_to_utf8(user, sizeof(user), username());
-        latin1_to_utf8(pass, sizeof(pass), passwd);
-        xstrncpy(user, rfc1738_escape(user), sizeof(user));
-        xstrncpy(pass, rfc1738_escape(pass), sizeof(pass));
-    } else {
-        xstrncpy(user, rfc1738_escape(username()), sizeof(user));
-        xstrncpy(pass, rfc1738_escape(passwd), sizeof(pass));
-    }
-    snprintf(buf, sizeof(buf), "%s %s\n", user, pass);
-    helperSubmit(basicauthenticators, buf, authenticateBasicHandleReply, r);
-}
-
-AuthConfig *
-basicScheme::createConfig()
+Auth::Basic::Config::registerWithCacheManager(void)
 {
-    return &basicConfig;
+    Mgr::RegisterAction("basicauthenticator",
+                        "Basic User Authenticator Stats",
+                        authenticateBasicStats, 0, 1);
 }
