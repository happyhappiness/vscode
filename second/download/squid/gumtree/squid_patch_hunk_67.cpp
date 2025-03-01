 
 /* The functions in this file handle authentication.
  * They DO NOT perform access control or auditing.
  * See acl.c for access control and client_side.c for auditing */
 
 
-#include "squid.h"
-#include "auth_negotiate.h"
+#include "squid-old.h"
+#include "auth/negotiate/auth_negotiate.h"
 #include "auth/Gadgets.h"
-#include "CacheManager.h"
+#include "auth/State.h"
+#include "mgr/Registration.h"
 #include "Store.h"
 #include "client_side.h"
 #include "HttpReply.h"
 #include "HttpRequest.h"
 #include "SquidTime.h"
-/** \todo remove this include */
-#include "negotiateScheme.h"
+#include "auth/negotiate/Scheme.h"
+#include "auth/negotiate/User.h"
+#include "auth/negotiate/UserRequest.h"
 #include "wordlist.h"
 
 /**
  \defgroup AuthNegotiateInternal Negotiate Authenticator Internals
  \ingroup AuthNegotiateAPI
  */
 
-/**
- * Maximum length (buffer size) for token strings.
- */
-// AYJ: must match re-definition in helpers/negotiate_auth/squid_kerb_auth/squid_kerb_auth.c
-#define MAX_AUTHTOKEN_LEN   32768
-
-
-/// \ingroup AuthNegotiateInternal
-static void
-authenticateStateFree(authenticateStateData * r)
-{
-    AUTHUSERREQUESTUNLOCK(r->auth_user_request, "r");
-    cbdataFree(r);
-}
-
 /* Negotiate Scheme */
-static HLPSCB authenticateNegotiateHandleReply;
 static AUTHSSTATS authenticateNegotiateStats;
 
 /// \ingroup AuthNegotiateInternal
-static statefulhelper *negotiateauthenticators = NULL;
-
-CBDATA_TYPE(authenticateStateData);
+statefulhelper *negotiateauthenticators = NULL;
 
 /// \ingroup AuthNegotiateInternal
 static int authnegotiate_initialised = 0;
 
 /// \ingroup AuthNegotiateInternal
-static auth_negotiate_config negotiateConfig;
-
-/// \ingroup AuthNegotiateInternal
 static hash_table *proxy_auth_cache = NULL;
 
 /*
  *
  * Private Functions
  *
  */
 
-/**
- \ingroup AuthNegotiateInternal
- \todo move to negotiateScheme.cc
- */
 void
-negotiateScheme::done()
+Auth::Negotiate::Config::rotateHelpers()
 {
-    /* TODO: this should be a Config call. */
-    debugs(29, 2, "negotiateScheme::done: shutting down Negotiate authentication.");
-
-    if (negotiateauthenticators)
+    /* schedule closure of existing helpers */
+    if (negotiateauthenticators) {
         helperStatefulShutdown(negotiateauthenticators);
+    }
+
+    /* NP: dynamic helper restart will ensure they start up again as needed. */
+}
 
+void
+Auth::Negotiate::Config::done()
+{
     authnegotiate_initialised = 0;
 
+    if (negotiateauthenticators) {
+        helperStatefulShutdown(negotiateauthenticators);
+    }
+
     if (!shutting_down)
         return;
 
-    if (negotiateauthenticators)
-        helperStatefulFree(negotiateauthenticators);
-
+    delete negotiateauthenticators;
     negotiateauthenticators = NULL;
 
-    debugs(29, 2, "negotiateScheme::done: Negotiate authentication Shutdown.");
-}
+    if (authenticateProgram)
+        wordlistDestroy(&authenticateProgram);
 
-void
-AuthNegotiateConfig::done()
-{
-    if (authenticate)
-        wordlistDestroy(&authenticate);
+    debugs(29, DBG_IMPORTANT, "Reconfigure: Negotiate authentication configuration cleared.");
 }
 
 void
-AuthNegotiateConfig::dump(StoreEntry * entry, const char *name, AuthConfig * scheme)
+Auth::Negotiate::Config::dump(StoreEntry * entry, const char *name, Auth::Config * scheme)
 {
-    wordlist *list = authenticate;
+    wordlist *list = authenticateProgram;
     storeAppendPrintf(entry, "%s %s", name, "negotiate");
 
     while (list != NULL) {
         storeAppendPrintf(entry, " %s", list->key);
         list = list->next;
     }
 
-    storeAppendPrintf(entry, "\n%s negotiate children %d\n",
-                      name, authenticateChildren);
+    storeAppendPrintf(entry, "\n%s negotiate children %d startup=%d idle=%d concurrency=%d\n",
+                      name, authenticateChildren.n_max, authenticateChildren.n_startup, authenticateChildren.n_idle, authenticateChildren.concurrency);
     storeAppendPrintf(entry, "%s %s keep_alive %s\n", name, "negotiate", keep_alive ? "on" : "off");
 
 }
 
-AuthNegotiateConfig::AuthNegotiateConfig() : authenticateChildren(5), keep_alive(0)
+Auth::Negotiate::Config::Config() : keep_alive(1)
 { }
 
 void
-AuthNegotiateConfig::parse(AuthConfig * scheme, int n_configured, char *param_str)
+Auth::Negotiate::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
 {
     if (strcasecmp(param_str, "program") == 0) {
-        if (authenticate)
-            wordlistDestroy(&authenticate);
+        if (authenticateProgram)
+            wordlistDestroy(&authenticateProgram);
 
-        parse_wordlist(&authenticate);
+        parse_wordlist(&authenticateProgram);
 
-        requirePathnameExists("auth_param negotiate program", authenticate->key);
+        requirePathnameExists("auth_param negotiate program", authenticateProgram->key);
     } else if (strcasecmp(param_str, "children") == 0) {
-        parse_int(&authenticateChildren);
+        authenticateChildren.parseConfig();
     } else if (strcasecmp(param_str, "keep_alive") == 0) {
         parse_onoff(&keep_alive);
     } else {
-        debugs(29, 0, "AuthNegotiateConfig::parse: unrecognised negotiate auth scheme parameter '" << param_str << "'");
+        debugs(29, DBG_CRITICAL, "ERROR: unrecognised Negotiate auth scheme parameter '" << param_str << "'");
     }
 }
 
 const char *
-AuthNegotiateConfig::type() const
+Auth::Negotiate::Config::type() const
 {
-    return negotiateScheme::GetInstance().type();
+    return Auth::Negotiate::Scheme::GetInstance()->type();
 }
 
 /**
  * Initialize helpers and the like for this auth scheme.
  * Called AFTER parsing the config file
  */
 void
-AuthNegotiateConfig::init(AuthConfig * scheme)
+Auth::Negotiate::Config::init(Auth::Config * scheme)
 {
-    if (authenticate) {
+    if (authenticateProgram) {
 
         authnegotiate_initialised = 1;
 
         if (negotiateauthenticators == NULL)
-            negotiateauthenticators = helperStatefulCreate("negotiateauthenticator");
+            negotiateauthenticators = new statefulhelper("negotiateauthenticator");
 
         if (!proxy_auth_cache)
             proxy_auth_cache = hash_create((HASHCMP *) strcmp, 7921, hash_string);
 
         assert(proxy_auth_cache);
 
-        negotiateauthenticators->cmdline = authenticate;
+        negotiateauthenticators->cmdline = authenticateProgram;
 
-        negotiateauthenticators->n_to_start = authenticateChildren;
+        negotiateauthenticators->childs.updateLimits(authenticateChildren);
 
         negotiateauthenticators->ipc_type = IPC_STREAM;
 
         helperStatefulOpenServers(negotiateauthenticators);
-
-        CBDATA_INIT_TYPE(authenticateStateData);
     }
 }
 
 void
-AuthNegotiateConfig::registerWithCacheManager(void)
+Auth::Negotiate::Config::registerWithCacheManager(void)
 {
-    CacheManager::GetInstance()->
-    registerAction("negotiateauthenticator",
-                   "Negotiate User Authenticator Stats",
-                   authenticateNegotiateStats, 0, 1);
+    Mgr::RegisterAction("negotiateauthenticator",
+                        "Negotiate User Authenticator Stats",
+                        authenticateNegotiateStats, 0, 1);
 }
 
 bool
-AuthNegotiateConfig::active() const
+Auth::Negotiate::Config::active() const
 {
     return authnegotiate_initialised == 1;
 }
 
 bool
-AuthNegotiateConfig::configured() const
+Auth::Negotiate::Config::configured() const
 {
-    if ((authenticate != NULL) && (authenticateChildren != 0)) {
-        debugs(29, 9, "AuthNegotiateConfig::configured: returning configured");
+    if (authenticateProgram && (authenticateChildren.n_max != 0)) {
+        debugs(29, 9, HERE << "returning configured");
         return true;
     }
 
-    debugs(29, 9, "AuthNegotiateConfig::configured: returning unconfigured");
+    debugs(29, 9, HERE << "returning unconfigured");
     return false;
 }
 
 /* Negotiate Scheme */
-/* See AuthUserRequest.cc::authenticateDirection for return values */
-int
-AuthNegotiateUserRequest::module_direction()
-{
-    /* null auth_user is checked for by authenticateDirection */
-
-    if (waiting || client_blob)
-        return -1; /* need helper response to continue */
-
-    switch (auth_state) {
-
-        /* no progress at all. */
-
-    case AUTHENTICATE_STATE_NONE:
-        debugs(29, 1, "AuthNegotiateUserRequest::direction: called before Negotiate Authenticate for request " << this << "!. Report a bug to squid-dev.");
-        return -2; /* error */
-
-    case AUTHENTICATE_STATE_FAILED:
-        return -2; /* error */
-
-
-    case AUTHENTICATE_STATE_IN_PROGRESS:
-        assert(server_blob);
-        return 1; /* send to client */
-
-    case AUTHENTICATE_STATE_DONE:
-        return 0; /* do nothing */
-
-    case AUTHENTICATE_STATE_INITIAL:
-        debugs(29, 1, "AuthNegotiateUserRequest::direction: Unexpected AUTHENTICATE_STATE_INITIAL");
-        return -2;
-    }
-
-    return -2;
-}
-
-/* add the [proxy]authorisation header */
-void
-AuthNegotiateUserRequest::addHeader(HttpReply * rep, int accel)
-{
-    http_hdr_type type;
-
-    if (!server_blob)
-        return;
-
-    /* don't add to authentication error pages */
-
-    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
-            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
-        return;
-
-    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;
-
-    httpHeaderPutStrf(&rep->header, type, "Negotiate %s", server_blob);
-
-    safe_free(server_blob);
-}
 
 void
-AuthNegotiateConfig::fixHeader(AuthUserRequest *auth_user_request, HttpReply *rep, http_hdr_type reqType, HttpRequest * request)
+Auth::Negotiate::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type reqType, HttpRequest * request)
 {
-    AuthNegotiateUserRequest *negotiate_request;
-
-    if (!authenticate)
+    if (!authenticateProgram)
         return;
 
     /* Need keep-alive */
     if (!request->flags.proxy_keepalive && request->flags.must_keepalive)
         return;
 
     /* New request, no user details */
     if (auth_user_request == NULL) {
-        debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate'");
+        debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate'");
         httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
 
         if (!keep_alive) {
             /* drop the connection */
             rep->header.delByName("keep-alive");
             request->flags.proxy_keepalive = 0;
         }
     } else {
-        negotiate_request = dynamic_cast<AuthNegotiateUserRequest *>(auth_user_request);
-
+        Auth::Negotiate::UserRequest *negotiate_request = dynamic_cast<Auth::Negotiate::UserRequest *>(auth_user_request.getRaw());
         assert(negotiate_request != NULL);
 
-        switch (negotiate_request->auth_state) {
+        switch (negotiate_request->user()->credentials()) {
 
-        case AUTHENTICATE_STATE_FAILED:
+        case Auth::Failed:
             /* here it makes sense to drop the connection, as auth is
              * tied to it, even if MAYBE the client could handle it - Kinkie */
             rep->header.delByName("keep-alive");
             request->flags.proxy_keepalive = 0;
             /* fall through */
 
-        case AUTHENTICATE_STATE_DONE:
+        case Auth::Ok:
             /* Special case: authentication finished OK but disallowed by ACL.
              * Need to start over to give the client another chance.
              */
-
             if (negotiate_request->server_blob) {
-                debugs(29, 9, "authenticateNegotiateFixErrorHeader: Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
+                debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
                 httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
                 safe_free(negotiate_request->server_blob);
             } else {
-                debugs(29, 9, "authenticateNegotiateFixErrorHeader: Connection authenticated");
+                debugs(29, 9, HERE << "Connection authenticated");
                 httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
             }
-
             break;
 
-        case AUTHENTICATE_STATE_NONE:
+        case Auth::Unchecked:
             /* semantic change: do not drop the connection.
              * 2.5 implementation used to keep it open - Kinkie */
-            debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate'");
+            debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate'");
             httpHeaderPutStrf(&rep->header, reqType, "Negotiate");
             break;
 
-        case AUTHENTICATE_STATE_IN_PROGRESS:
+        case Auth::Handshake:
             /* we're waiting for a response from the client. Pass it the blob */
-            debugs(29, 9, "AuthNegotiateConfig::fixHeader: Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
+            debugs(29, 9, HERE << "Sending type:" << reqType << " header: 'Negotiate " << negotiate_request->server_blob << "'");
             httpHeaderPutStrf(&rep->header, reqType, "Negotiate %s", negotiate_request->server_blob);
             safe_free(negotiate_request->server_blob);
             break;
 
-
         default:
-            debugs(29, 0, "AuthNegotiateConfig::fixHeader: state " << negotiate_request->auth_state << ".");
+            debugs(29, DBG_CRITICAL, "ERROR: Negotiate auth fixHeader: state " << negotiate_request->user()->credentials() << ".");
             fatal("unexpected state in AuthenticateNegotiateFixErrorHeader.\n");
         }
     }
 }
 
-NegotiateUser::~NegotiateUser()
-{
-    debugs(29, 5, "NegotiateUser::~NegotiateUser: doing nothing to clearNegotiate scheme data for '" << this << "'");
-}
-
-static void
-authenticateNegotiateHandleReply(void *data, void *lastserver, char *reply)
-{
-    authenticateStateData *r = static_cast<authenticateStateData *>(data);
-
-    int valid;
-    char *blob, *arg = NULL;
-
-    AuthUserRequest *auth_user_request;
-    AuthUser *auth_user;
-    NegotiateUser *negotiate_user;
-    AuthNegotiateUserRequest *negotiate_request;
-
-    debugs(29, 8, "authenticateNegotiateHandleReply: helper: '" << lastserver << "' sent us '" << (reply ? reply : "<NULL>") << "'");
-    valid = cbdataReferenceValid(r->data);
-
-    if (!valid) {
-        debugs(29, 1, "authenticateNegotiateHandleReply: invalid callback data. helper '" << lastserver << "'.");
-        cbdataReferenceDone(r->data);
-        authenticateStateFree(r);
-        return;
-    }
-
-    if (!reply) {
-        debugs(29, 1, "authenticateNegotiateHandleReply: Helper '" << lastserver << "' crashed!.");
-        reply = (char *)"BH Internal error";
-    }
-
-    auth_user_request = r->auth_user_request;
-    assert(auth_user_request != NULL);
-    negotiate_request = dynamic_cast<AuthNegotiateUserRequest *>(auth_user_request);
-
-    assert(negotiate_request != NULL);
-    assert(negotiate_request->waiting);
-    negotiate_request->waiting = 0;
-    safe_free(negotiate_request->client_blob);
-
-    auth_user = negotiate_request->user();
-    assert(auth_user != NULL);
-    assert(auth_user->auth_type == AUTH_NEGOTIATE);
-    negotiate_user = dynamic_cast<negotiate_user_t *>(auth_user_request->user());
-
-    assert(negotiate_user != NULL);
-
-    if (negotiate_request->authserver == NULL)
-        negotiate_request->authserver = static_cast<helper_stateful_server*>(lastserver);
-    else
-        assert(negotiate_request->authserver == lastserver);
-
-    /* seperate out the useful data */
-    blob = strchr(reply, ' ');
-
-    if (blob) {
-        blob++;
-        arg = strchr(blob + 1, ' ');
-    } else {
-        arg = NULL;
-    }
-
-    if (strncasecmp(reply, "TT ", 3) == 0) {
-        /* we have been given a blob to send to the client */
-        if (arg)
-            *arg++ = '\0';
-        safe_free(negotiate_request->server_blob);
-        negotiate_request->request->flags.must_keepalive = 1;
-        if (negotiate_request->request->flags.proxy_keepalive) {
-            negotiate_request->server_blob = xstrdup(blob);
-            negotiate_request->auth_state = AUTHENTICATE_STATE_IN_PROGRESS;
-            auth_user_request->denyMessage("Authentication in progress");
-            debugs(29, 4, "authenticateNegotiateHandleReply: Need to challenge the client with a server blob '" << blob << "'");
-        } else {
-            negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;
-            auth_user_request->denyMessage("NTLM authentication requires a persistent connection");
-        }
-    } else if (strncasecmp(reply, "AF ", 3) == 0 && arg != NULL) {
-        /* we're finished, release the helper */
-
-        if (arg)
-            *arg++ = '\0';
-
-        negotiate_user->username(arg);
-
-        auth_user_request->denyMessage("Login successful");
-
-        safe_free(negotiate_request->server_blob);
-
-        negotiate_request->server_blob = xstrdup(blob);
-
-        negotiate_request->releaseAuthServer();
-
-        negotiate_request->auth_state = AUTHENTICATE_STATE_DONE;
-
-        debugs(29, 4, "authenticateNegotiateHandleReply: Successfully validated user via Negotiate. Username '" << blob << "'");
-
-        /* connection is authenticated */
-        debugs(29, 4, "AuthNegotiateUserRequest::authenticate: authenticated user " << negotiate_user->username());
-        /* see if this is an existing user with a different proxy_auth
-         * string */
-        AuthUserHashPointer *usernamehash = static_cast<AuthUserHashPointer *>(hash_lookup(proxy_auth_username_cache, negotiate_user->username()));
-        AuthUser *local_auth_user = negotiate_request->user();
-        while (usernamehash && (usernamehash->user()->auth_type != AUTH_NEGOTIATE || strcmp(usernamehash->user()->username(), negotiate_user->username()) != 0))
-            usernamehash = static_cast<AuthUserHashPointer *>(usernamehash->next);
-        if (usernamehash) {
-            /* we can't seamlessly recheck the username due to the
-             * challenge-response nature of the protocol.
-             * Just free the temporary auth_user */
-            usernamehash->user()->absorb(local_auth_user);
-            //authenticateAuthUserMerge(local_auth_user, usernamehash->user());
-            local_auth_user = usernamehash->user();
-            negotiate_request->_auth_user = local_auth_user;
-        } else {
-            /* store user in hash's */
-            local_auth_user->addToNameCache();
-            // authenticateUserNameCacheAdd(local_auth_user);
-        }
-        /* set these to now because this is either a new login from an
-         * existing user or a new user */
-        local_auth_user->expiretime = current_time.tv_sec;
-        negotiate_request->releaseAuthServer();
-        negotiate_request->auth_state = AUTHENTICATE_STATE_DONE;
-
-    } else if (strncasecmp(reply, "NA ", 3) == 0 && arg != NULL) {
-        /* authentication failure (wrong password, etc.) */
-
-        if (arg)
-            *arg++ = '\0';
-
-        auth_user_request->denyMessage(arg);
-
-        negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;
-
-        safe_free(negotiate_request->server_blob);
-
-        negotiate_request->server_blob = xstrdup(blob);
-
-        negotiate_request->releaseAuthServer();
-
-        debugs(29, 4, "authenticateNegotiateHandleReply: Failed validating user via Negotiate. Error returned '" << blob << "'");
-    } else if (strncasecmp(reply, "BH ", 3) == 0) {
-        /* TODO kick off a refresh process. This can occur after a YR or after
-         * a KK. If after a YR release the helper and resubmit the request via
-         * Authenticate Negotiate start.
-         * If after a KK deny the user's request w/ 407 and mark the helper as
-         * Needing YR. */
-        auth_user_request->denyMessage(blob);
-        negotiate_request->auth_state = AUTHENTICATE_STATE_FAILED;
-        safe_free(negotiate_request->server_blob);
-        negotiate_request->releaseAuthServer();
-        debugs(29, 1, "authenticateNegotiateHandleReply: Error validating user via Negotiate. Error returned '" << reply << "'");
-    } else {
-        /* protocol error */
-        fatalf("authenticateNegotiateHandleReply: *** Unsupported helper response ***, '%s'\n", reply);
-    }
-
-    if (negotiate_request->request) {
-        HTTPMSGUNLOCK(negotiate_request->request);
-        negotiate_request->request = NULL;
-    }
-    r->handler(r->data, NULL);
-    cbdataReferenceDone(r->data);
-    authenticateStateFree(r);
-}
-
 static void
 authenticateNegotiateStats(StoreEntry * sentry)
 {
     helperStatefulStats(sentry, negotiateauthenticators, "Negotiate Authenticator Statistics");
 }
 
-
-/** send the initial data to a stateful negotiate authenticator module */
-void
-AuthNegotiateUserRequest::module_start(RH * handler, void *data)
-{
-    authenticateStateData *r = NULL;
-    static char buf[MAX_AUTHTOKEN_LEN];
-    AuthUser *auth_user = user();
-
-    assert(data);
-    assert(handler);
-    assert(auth_user);
-    assert(auth_user->auth_type == AUTH_NEGOTIATE);
-
-    debugs(29, 8, "AuthNegotiateUserRequest::module_start: auth state is '" << auth_state << "'");
-
-    if (negotiateConfig.authenticate == NULL) {
-        debugs(29, 0, "AuthNegotiateUserRequest::module_start: no Negotiate program specified.");
-        handler(data, NULL);
-        return;
-    }
-
-    r = cbdataAlloc(authenticateStateData);
-    r->handler = handler;
-    r->data = cbdataReference(data);
-    r->auth_user_request = this;
-    AUTHUSERREQUESTLOCK(r->auth_user_request, "r");
-
-    if (auth_state == AUTHENTICATE_STATE_INITIAL) {
-        snprintf(buf, MAX_AUTHTOKEN_LEN, "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
-    } else {
-        snprintf(buf, MAX_AUTHTOKEN_LEN, "KK %s\n", client_blob);
-    }
-
-    waiting = 1;
-
-    safe_free(client_blob);
-    helperStatefulSubmit(negotiateauthenticators, buf, authenticateNegotiateHandleReply, r, authserver);
-}
-
-/**
- * Atomic action: properly release the Negotiate auth helpers which may have been reserved
- * for this request connections use.
- */
-void
-AuthNegotiateUserRequest::releaseAuthServer()
-{
-    if (authserver) {
-        debugs(29, 6, HERE << "releasing Negotiate auth server '" << authserver << "'");
-        helperStatefulReleaseServer(authserver);
-        authserver = NULL;
-    } else
-        debugs(29, 6, HERE << "No Negotiate auth server to release.");
-}
-
-/* clear any connection related authentication details */
-void
-AuthNegotiateUserRequest::onConnectionClose(ConnStateData *conn)
-{
-    assert(conn != NULL);
-
-    debugs(29, 8, "AuthNegotiateUserRequest::onConnectionClose: closing connection '" << conn << "' (this is '" << this << "')");
-
-    if (conn->auth_user_request == NULL) {
-        debugs(29, 8, "AuthNegotiateUserRequest::onConnectionClose: no auth_user_request");
-        return;
-    }
-
-    releaseAuthServer();
-
-    /* unlock the connection based lock */
-    debugs(29, 9, "AuthNegotiateUserRequest::onConnectionClose: Unlocking auth_user from the connection '" << conn << "'.");
-
-    AUTHUSERREQUESTUNLOCK(conn->auth_user_request, "conn");
-}
-
 /*
  * Decode a Negotiate [Proxy-]Auth string, placing the results in the passed
  * Auth_user structure.
  */
-AuthUserRequest *
-AuthNegotiateConfig::decode(char const *proxy_auth)
+Auth::UserRequest::Pointer
+Auth::Negotiate::Config::decode(char const *proxy_auth)
 {
-    NegotiateUser *newUser = new NegotiateUser(&negotiateConfig);
-    AuthNegotiateUserRequest *auth_user_request = new AuthNegotiateUserRequest ();
+    Auth::Negotiate::User *newUser = new Auth::Negotiate::User(Auth::Config::Find("negotiate"));
+    Auth::UserRequest *auth_user_request = new Auth::Negotiate::UserRequest();
     assert(auth_user_request->user() == NULL);
+
     auth_user_request->user(newUser);
-    auth_user_request->user()->auth_type = AUTH_NEGOTIATE;
-    auth_user_request->user()->addRequest(auth_user_request);
+    auth_user_request->user()->auth_type = Auth::AUTH_NEGOTIATE;
 
     /* all we have to do is identify that it's Negotiate - the helper does the rest */
-    debugs(29, 9, "AuthNegotiateConfig::decode: Negotiate authentication");
+    debugs(29, 9, HERE << "decode Negotiate authentication");
     return auth_user_request;
 }
-
-int
-AuthNegotiateUserRequest::authenticated() const
-{
-    if (auth_state == AUTHENTICATE_STATE_DONE) {
-        debugs(29, 9, "AuthNegotiateUserRequest::authenticated: user authenticated.");
-        return 1;
-    }
-
-    debugs(29, 9, "AuthNegotiateUserRequest::authenticated: user not fully authenticated.");
-
-    return 0;
-}
-
-void
-AuthNegotiateUserRequest::authenticate(HttpRequest * aRequest, ConnStateData * conn, http_hdr_type type)
-{
-    const char *proxy_auth, *blob;
-
-    /** \todo rename this!! */
-    AuthUser *local_auth_user;
-
-    local_auth_user = user();
-    assert(local_auth_user);
-    assert(local_auth_user->auth_type == AUTH_NEGOTIATE);
-    assert (this);
-
-    /** Check that we are in the client side, where we can generate
-     * auth challenges */
-
-    if (conn == NULL) {
-        auth_state = AUTHENTICATE_STATE_FAILED;
-        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: attempt to perform authentication without a connection!");
-        return;
-    }
-
-    if (waiting) {
-        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: waiting for helper reply!");
-        return;
-    }
-
-    if (server_blob) {
-        debugs(29, 2, "AuthNegotiateUserRequest::authenticate: need to challenge client '" << server_blob << "'!");
-        return;
-    }
-
-    /* get header */
-    proxy_auth = aRequest->header.getStr(type);
-
-    /* locate second word */
-    blob = proxy_auth;
-
-    if (blob) {
-        while (xisspace(*blob) && *blob)
-            blob++;
-
-        while (!xisspace(*blob) && *blob)
-            blob++;
-
-        while (xisspace(*blob) && *blob)
-            blob++;
-    }
-
-    switch (auth_state) {
-
-    case AUTHENTICATE_STATE_NONE:
-        /* we've received a negotiate request. pass to a helper */
-        debugs(29, 9, "AuthNegotiateUserRequest::authenticate: auth state negotiate none. Received blob: '" << proxy_auth << "'");
-        auth_state = AUTHENTICATE_STATE_INITIAL;
-        safe_free(client_blob);
-        client_blob=xstrdup(blob);
-        conn->auth_type = AUTH_NEGOTIATE;
-        assert(conn->auth_user_request == NULL);
-        conn->auth_user_request = this;
-        AUTHUSERREQUESTLOCK(conn->auth_user_request, "conn");
-        request = aRequest;
-        HTTPMSGLOCK(request);
-        return;
-
-        break;
-
-    case AUTHENTICATE_STATE_INITIAL:
-        debugs(29, 1, "AuthNegotiateUserRequest::authenticate: need to ask helper");
-
-        return;
-
-        break;
-
-
-    case AUTHENTICATE_STATE_IN_PROGRESS:
-        /* we should have received a blob from the client. Hand it off to
-         * some helper */
-        safe_free(client_blob);
-
-        client_blob = xstrdup (blob);
-
-        if (request)
-            HTTPMSGUNLOCK(request);
-        request = aRequest;
-        HTTPMSGLOCK(request);
-        return;
-
-        break;
-
-    case AUTHENTICATE_STATE_DONE:
-        fatal("AuthNegotiateUserRequest::authenticate: unexpect auth state DONE! Report a bug to the squid developers.\n");
-
-        break;
-
-    case AUTHENTICATE_STATE_FAILED:
-        /* we've failed somewhere in authentication */
-        debugs(29, 9, "AuthNegotiateUserRequest::authenticate: auth state negotiate failed. " << proxy_auth);
-
-        return;
-
-        break;
-    }
-
-    return;
-}
-
-AuthNegotiateUserRequest::AuthNegotiateUserRequest() :
-        /*conn(NULL),*/ auth_state(AUTHENTICATE_STATE_NONE)
-{
-    waiting=0;
-    client_blob=0;
-    server_blob=0;
-    authserver=NULL;
-    request=NULL;
-}
-
-AuthNegotiateUserRequest::~AuthNegotiateUserRequest()
-{
-    safe_free(server_blob);
-    safe_free(client_blob);
-
-    if (authserver != NULL) {
-        debugs(29, 9, "AuthNegotiateUserRequest::~AuthNegotiateUserRequest: releasing server '" << authserver << "'");
-        helperStatefulReleaseServer(authserver);
-        authserver = NULL;
-    }
-    if (request) {
-        HTTPMSGUNLOCK(request);
-        request = NULL;
-    }
-}
-
-void
-NegotiateUser::deleteSelf() const
-{
-    delete this;
-}
-
-NegotiateUser::NegotiateUser (AuthConfig *aConfig) : AuthUser (aConfig)
-{
-    proxy_auth_list.head = proxy_auth_list.tail = NULL;
-}
-
-AuthConfig *
-negotiateScheme::createConfig()
-{
-    return &negotiateConfig;
-}
-
-const char *
-AuthNegotiateUserRequest::connLastHeader()
-{
-    return NULL;
-}
-
