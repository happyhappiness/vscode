 /**
  \ingroup CacheManagerInternal
  * Locates an action in the actions registry ActionsList.
 \retval NULL  if Action not found
 \retval CacheManagerAction* if the action was found
  */
-CacheManagerAction *
-CacheManager::findAction(char const * action)
+Mgr::ActionProfile::Pointer
+CacheManager::findAction(char const * action) const
 {
-    CacheManagerActionList::iterator a;
+    Must(action != NULL);
+    Menu::const_iterator a;
 
     debugs(16, 5, "CacheManager::findAction: looking for action " << action);
-    for ( a = ActionsList.begin(); a != ActionsList.end(); a++) {
-        if (0 == strcmp((*a)->action, action)) {
+    for (a = menu_.begin(); a != menu_.end(); ++a) {
+        if (0 == strcmp((*a)->name, action)) {
             debugs(16, 6, " found");
             return *a;
         }
     }
 
     debugs(16, 6, "Action not found.");
-    return NULL;
+    return Mgr::ActionProfilePointer();
+}
+
+Mgr::Action::Pointer
+CacheManager::createNamedAction(const char *actionName)
+{
+    Must(actionName);
+
+    Mgr::Command::Pointer cmd = new Mgr::Command;
+    cmd->profile = findAction(actionName);
+    cmd->params.actionName = actionName;
+
+    Must(cmd->profile != NULL);
+    return cmd->profile->creator->create(cmd);
+}
+
+Mgr::Action::Pointer
+CacheManager::createRequestedAction(const Mgr::ActionParams &params)
+{
+    Mgr::Command::Pointer cmd = new Mgr::Command;
+    cmd->params = params;
+    cmd->profile = findAction(params.actionName.termedBuf());
+    Must(cmd->profile != NULL);
+    return cmd->profile->creator->create(cmd);
 }
 
 /**
  \ingroup CacheManagerInternal
  * define whether the URL is a cache-manager URL and parse the action
  * requested by the user. Checks via CacheManager::ActionProtection() that the
  * item is accessible by the user.
  \retval CacheManager::cachemgrStateData state object for the following handling
  \retval NULL if the action can't be found or can't be accessed by the user
  */
-CacheManager::cachemgrStateData *
+Mgr::Command::Pointer
 CacheManager::ParseUrl(const char *url)
 {
     int t;
     LOCAL_ARRAY(char, host, MAX_URL);
     LOCAL_ARRAY(char, request, MAX_URL);
     LOCAL_ARRAY(char, password, MAX_URL);
-    CacheManagerAction *a;
-    cachemgrStateData *mgr = NULL;
-    const char *prot;
-    t = sscanf(url, "cache_object://%[^/]/%[^@]@%s", host, request, password);
-
+    LOCAL_ARRAY(char, params, MAX_URL);
+    host[0] = 0;
+    request[0] = 0;
+    password[0] = 0;
+    params[0] = 0;
+    int pos = -1;
+    int len = strlen(url);
+    Must(len > 0);
+    t = sscanf(url, "cache_object://%[^/]/%[^@?]%n@%[^?]?%s", host, request, &pos, password, params);
+    if (t < 3) {
+        t = sscanf(url, "cache_object://%[^/]/%[^?]%n?%s", host, request, &pos, params);
+    }
+    if (t < 1) {
+        t = sscanf(url, "http://%[^/]/squid-internal-mgr/%[^?]%n?%s", host, request, &pos, params);
+    }
+    if (t < 1) {
+        t = sscanf(url, "https://%[^/]/squid-internal-mgr/%[^?]%n?%s", host, request, &pos, params);
+    }
     if (t < 2) {
-        xstrncpy(request, "menu", MAX_URL);
-#ifdef _SQUID_OS2_
+        if (strncmp("cache_object://",url,15)==0)
+            xstrncpy(request, "menu", MAX_URL);
+        else
+            xstrncpy(request, "index", MAX_URL);
+    }
+
+#if _SQUID_OS2_
+    if (t == 2 && request[0] == '\0') {
         /*
          * emx's sscanf insists of returning 2 because it sets request
          * to null
          */
-    } else if (request[0] == '\0') {
-        xstrncpy(request, "menu", MAX_URL);
+        if (strncmp("cache_object://",url,15)==0)
+            xstrncpy(request, "menu", MAX_URL);
+        else
+            xstrncpy(request, "index", MAX_URL);
+    }
 #endif
 
-    } else if ((a = findAction(request)) == NULL) {
+    debugs(16, 3, HERE << "MGR request: t=" << t << ", host='" << host << "', request='" << request << "', pos=" << pos <<
+           ", password='" << password << "', params='" << params << "'");
+
+    Mgr::ActionProfile::Pointer profile = findAction(request);
+    if (!profile) {
         debugs(16, DBG_IMPORTANT, "CacheManager::ParseUrl: action '" << request << "' not found");
         return NULL;
-    } else {
-        prot = ActionProtection(a);
-
-        if (!strcmp(prot, "disabled") || !strcmp(prot, "hidden")) {
-            debugs(16, DBG_IMPORTANT, "CacheManager::ParseUrl: action '" << request << "' is " << prot);
-            return NULL;
-        }
     }
 
-    /* set absent entries to NULL so we can test if they are present later */
-    mgr = (cachemgrStateData *)xcalloc(1, sizeof(cachemgrStateData));
-
-    mgr->user_name = NULL;
-
-    mgr->passwd = t == 3 ? xstrdup(password) : NULL;
-
-    mgr->action = xstrdup(request);
+    const char *prot = ActionProtection(profile);
+    if (!strcmp(prot, "disabled") || !strcmp(prot, "hidden")) {
+        debugs(16, DBG_IMPORTANT, "CacheManager::ParseUrl: action '" << request << "' is " << prot);
+        return NULL;
+    }
 
-    return mgr;
+    Mgr::Command::Pointer cmd = new Mgr::Command;
+    if (!Mgr::QueryParams::Parse(params, cmd->params.queryParams))
+        return NULL;
+    cmd->profile = profile;
+    cmd->params.httpUri = url;
+    cmd->params.userName = String();
+    cmd->params.password = password;
+    cmd->params.actionName = request;
+    return cmd;
 }
 
 /// \ingroup CacheManagerInternal
 /*
  \ingroup CacheManagerInternal
  * Decodes the headers needed to perform user authentication and fills
  * the details into the cachemgrStateData argument
  */
 void
-CacheManager::ParseHeaders(cachemgrStateData * mgr, const HttpRequest * request)
+CacheManager::ParseHeaders(const HttpRequest * request, Mgr::ActionParams &params)
 {
-    const char *basic_cookie;	/* base 64 _decoded_ user:passwd pair */
-    const char *passwd_del;
-    assert(mgr && request);
-    basic_cookie = request->header.getAuth(HDR_AUTHORIZATION, "Basic");
+    assert(request);
+
+    params.httpMethod = request->method.id();
+    params.httpFlags = request->flags;
+
+#if HAVE_AUTH_MODULE_BASIC
+    // TODO: use the authentication system decode to retrieve these details properly.
+
+    /* base 64 _decoded_ user:passwd pair */
+    const char *basic_cookie = request->header.getAuth(HDR_AUTHORIZATION, "Basic");
 
     if (!basic_cookie)
         return;
 
+    const char *passwd_del;
     if (!(passwd_del = strchr(basic_cookie, ':'))) {
         debugs(16, DBG_IMPORTANT, "CacheManager::ParseHeaders: unknown basic_cookie format '" << basic_cookie << "'");
         return;
     }
 
     /* found user:password pair, reset old values */
-    safe_free(mgr->user_name);
-
-    safe_free(mgr->passwd);
-
-    mgr->user_name = xstrdup(basic_cookie);
+    params.userName.limitInit(basic_cookie, passwd_del - basic_cookie);
+    params.password = passwd_del + 1;
 
-    mgr->user_name[passwd_del - basic_cookie] = '\0';
-
-    mgr->passwd = xstrdup(passwd_del + 1);
-
-    /* warning: this prints decoded password which maybe not what you want to do @?@ @?@ */
-    debugs(16, 9, "CacheManager::ParseHeaders: got user: '" << mgr->user_name << "' passwd: '" << mgr->passwd << "'");
+    /* warning: this prints decoded password which maybe not be what you want to do @?@ @?@ */
+    debugs(16, 9, "CacheManager::ParseHeaders: got user: '" <<
+           params.userName << "' passwd: '" << params.password << "'");
+#endif
 }
 
 /**
  \ingroup CacheManagerInternal
  *
  \retval 0	if mgr->password is good or "none"
  \retval 1	if mgr->password is "disable"
  \retval !0	if mgr->password does not match configured password
  */
 int
-CacheManager::CheckPassword(cachemgrStateData * mgr)
+CacheManager::CheckPassword(const Mgr::Command &cmd)
 {
-    char *pwd = PasswdGet(Config.passwd_list, mgr->action);
-    CacheManagerAction *a = findAction(mgr->action);
+    assert(cmd.profile != NULL);
+    const char *action = cmd.profile->name;
+    char *pwd = PasswdGet(Config.passwd_list, action);
 
-    debugs(16, 4, "CacheManager::CheckPassword for action " << mgr->action);
-    assert(a != NULL);
+    debugs(16, 4, "CacheManager::CheckPassword for action " << action);
 
     if (pwd == NULL)
-        return a->flags.pw_req;
+        return cmd.profile->isPwReq;
 
     if (strcmp(pwd, "disable") == 0)
         return 1;
 
     if (strcmp(pwd, "none") == 0)
         return 0;
 
-    if (!mgr->passwd)
+    if (!cmd.params.password.size())
         return 1;
 
-    return strcmp(pwd, mgr->passwd);
-}
-
-/// \ingroup CacheManagerInternal
-void
-CacheManager::StateFree(cachemgrStateData * mgr)
-{
-    safe_free(mgr->action);
-    safe_free(mgr->user_name);
-    safe_free(mgr->passwd);
-    mgr->entry->unlock();
-    xfree(mgr);
+    return cmd.params.password != pwd;
 }
 
 /**
  \ingroup CacheManagerAPI
  * Main entry point in the Cache Manager's activity. Gets called as part
  * of the forward chain if the right URL is detected there. Initiates
  * all needed internal work and renders the response.
  */
 void
-CacheManager::Start(int fd, HttpRequest * request, StoreEntry * entry)
+CacheManager::Start(const Comm::ConnectionPointer &client, HttpRequest * request, StoreEntry * entry)
 {
-    cachemgrStateData *mgr = NULL;
-    ErrorState *err = NULL;
-    CacheManagerAction *a;
     debugs(16, 3, "CacheManager::Start: '" << entry->url() << "'" );
 
-    if ((mgr = ParseUrl(entry->url())) == NULL) {
-        err = errorCon(ERR_INVALID_URL, HTTP_NOT_FOUND, request);
+    Mgr::Command::Pointer cmd = ParseUrl(entry->url());
+    if (!cmd) {
+        ErrorState *err = new ErrorState(ERR_INVALID_URL, HTTP_NOT_FOUND, request);
         err->url = xstrdup(entry->url());
         errorAppendEntry(entry, err);
         entry->expires = squid_curtime;
         return;
     }
 
-    mgr->entry = entry;
+    const char *actionName = cmd->profile->name;
 
-    entry->lock();
     entry->expires = squid_curtime;
 
-    debugs(16, 5, "CacheManager: " << fd_table[fd].ipaddr << " requesting '" << mgr->action << "'");
+    debugs(16, 5, "CacheManager: " << client << " requesting '" << actionName << "'");
 
     /* get additional info from request headers */
-    ParseHeaders(mgr, request);
+    ParseHeaders(request, cmd->params);
+
+    const char *userName = cmd->params.userName.size() ?
+                           cmd->params.userName.termedBuf() : "unknown";
 
     /* Check password */
 
-    if (CheckPassword(mgr) != 0) {
+    if (CheckPassword(*cmd) != 0) {
         /* build error message */
-        ErrorState *errState;
-        HttpReply *rep;
-        errState = errorCon(ERR_CACHE_MGR_ACCESS_DENIED, HTTP_UNAUTHORIZED, request);
+        ErrorState errState(ERR_CACHE_MGR_ACCESS_DENIED, HTTP_UNAUTHORIZED, request);
         /* warn if user specified incorrect password */
 
-        if (mgr->passwd)
+        if (cmd->params.password.size()) {
             debugs(16, DBG_IMPORTANT, "CacheManager: " <<
-                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
-                   fd_table[fd].ipaddr << ": incorrect password for '" <<
-                   mgr->action << "'" );
-        else
+                   userName << "@" <<
+                   client << ": incorrect password for '" <<
+                   actionName << "'" );
+        } else {
             debugs(16, DBG_IMPORTANT, "CacheManager: " <<
-                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
-                   fd_table[fd].ipaddr << ": password needed for '" <<
-                   mgr->action << "'" );
-
-        rep = errState->BuildHttpReply();
+                   userName << "@" <<
+                   client << ": password needed for '" <<
+                   actionName << "'" );
+        }
 
-        errorStateFree(errState);
+        HttpReply *rep = errState.BuildHttpReply();
 
+#if HAVE_AUTH_MODULE_BASIC
         /*
-         * add Authenticate header, use 'action' as a realm because
-         * password depends on action
+         * add Authenticate header using action name as a realm because
+         * password depends on the action
          */
-        rep->header.putAuth("Basic", mgr->action);
+        rep->header.putAuth("Basic", actionName);
+#endif
+        // Allow cachemgr and other XHR scripts access to our version string
+        if (request->header.has(HDR_ORIGIN)) {
+            rep->header.putExt("Access-Control-Allow-Origin",request->header.getStr(HDR_ORIGIN));
+#if HAVE_AUTH_MODULE_BASIC
+            rep->header.putExt("Access-Control-Allow-Credentials","true");
+#endif
+            rep->header.putExt("Access-Control-Expose-Headers","Server");
+        }
 
         /* store the reply */
         entry->replaceHttpReply(rep);
 
         entry->expires = squid_curtime;
 
         entry->complete();
 
-        StateFree(mgr);
-
         return;
     }
 
-    debugs(16, 2, "CacheManager: " <<
-           (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
-           fd_table[fd].ipaddr << " requesting '" <<
-           mgr->action << "'" );
-    /* retrieve object requested */
-    a = findAction(mgr->action);
-    assert(a != NULL);
-
-    entry->buffer();
-
-    {
-        HttpReply *rep = new HttpReply;
-        rep->setHeaders(HTTP_OK, NULL, "text/plain", -1, squid_curtime, squid_curtime);
-        entry->replaceHttpReply(rep);
+    if (request->header.has(HDR_ORIGIN)) {
+        cmd->params.httpOrigin = request->header.getStr(HDR_ORIGIN);
     }
 
-    a->run(entry);
-
-    entry->flush();
-
-    if (a->flags.atomic)
+    debugs(16, 2, "CacheManager: " <<
+           userName << "@" <<
+           client << " requesting '" <<
+           actionName << "'" );
+
+    // special case: /squid-internal-mgr/ index page
+    if (!strcmp(cmd->profile->name, "index")) {
+        ErrorState err(MGR_INDEX, HTTP_OK, request);
+        err.url = xstrdup(entry->url());
+        HttpReply *rep = err.BuildHttpReply();
+        if (strncmp(rep->body.content(),"Internal Error:", 15) == 0)
+            rep->sline.status = HTTP_NOT_FOUND;
+        // Allow cachemgr and other XHR scripts access to our version string
+        if (request->header.has(HDR_ORIGIN)) {
+            rep->header.putExt("Access-Control-Allow-Origin",request->header.getStr(HDR_ORIGIN));
+#if HAVE_AUTH_MODULE_BASIC
+            rep->header.putExt("Access-Control-Allow-Credentials","true");
+#endif
+            rep->header.putExt("Access-Control-Expose-Headers","Server");
+        }
+        entry->replaceHttpReply(rep);
         entry->complete();
+        return;
+    }
 
-    StateFree(mgr);
-}
-
-/// \ingroup CacheManagerInternal
-void CacheManager::ShutdownAction::run(StoreEntry *sentry)
-{
-    debugs(16, DBG_CRITICAL, "Shutdown by Cache Manager command.");
-    shut_down(0);
-}
-/// \ingroup CacheManagerInternal
-CacheManager::ShutdownAction::ShutdownAction() : CacheManagerAction("shutdown","Shut Down the Squid Process", 1, 1) { }
-
-/// \ingroup CacheManagerInternal
-void
-CacheManager::ReconfigureAction::run(StoreEntry * sentry)
-{
-    debugs(16, DBG_IMPORTANT, "Reconfigure by Cache Manager command.");
-    storeAppendPrintf(sentry, "Reconfiguring Squid Process ....");
-    reconfigure(SIGHUP);
-}
-/// \ingroup CacheManagerInternal
-CacheManager::ReconfigureAction::ReconfigureAction() : CacheManagerAction("reconfigure","Reconfigure Squid", 1, 1) { }
-
-/// \ingroup CacheManagerInternal
-void
-CacheManager::OfflineToggleAction::run(StoreEntry * sentry)
-{
-    Config.onoff.offline = !Config.onoff.offline;
-    debugs(16, DBG_IMPORTANT, "offline_mode now " << (Config.onoff.offline ? "ON" : "OFF") << " by Cache Manager request.");
+    if (UsingSmp() && IamWorkerProcess()) {
+        // is client the right connection to pass here?
+        AsyncJob::Start(new Mgr::Forwarder(client, cmd->params, request, entry));
+        return;
+    }
 
-    storeAppendPrintf(sentry, "offline_mode is now %s\n",
-                      Config.onoff.offline ? "ON" : "OFF");
+    Mgr::Action::Pointer action = cmd->profile->creator->create(cmd);
+    Must(action != NULL);
+    action->run(entry, true);
 }
-/// \ingroup CacheManagerInternal
-CacheManager::OfflineToggleAction::OfflineToggleAction() : CacheManagerAction ("offline_toggle", "Toggle offline_mode setting", 1, 1) { }
 
 /*
  \ingroup CacheManagerInternal
  * Renders the protection level text for an action.
  * Also doubles as a check for the protection level.
  */
 const char *
-CacheManager::ActionProtection(const CacheManagerAction * at)
+CacheManager::ActionProtection(const Mgr::ActionProfile::Pointer &profile)
 {
-    char *pwd;
-    assert(at);
-    pwd = PasswdGet(Config.passwd_list, at->action);
+    assert(profile != NULL);
+    const char *pwd = PasswdGet(Config.passwd_list, profile->name);
 
     if (!pwd)
-        return at->flags.pw_req ? "hidden" : "public";
+        return profile->isPwReq ? "hidden" : "public";
 
     if (!strcmp(pwd, "disable"))
         return "disabled";
 
     if (strcmp(pwd, "none") == 0)
         return "public";
 
     return "protected";
 }
 
-/// \ingroup CacheManagerInternal
-void
-CacheManager::MenuAction::run(StoreEntry * sentry)
-{
-    CacheManagerActionList::iterator a;
-
-    debugs(16, 4, "CacheManager::MenuCommand invoked");
-    for (a = cmgr->ActionsList.begin(); a != cmgr->ActionsList.end(); ++a) {
-        debugs(16, 5, "  showing action " << (*a)->action);
-        storeAppendPrintf(sentry, " %-22s\t%-32s\t%s\n",
-                          (*a)->action, (*a)->desc, cmgr->ActionProtection(*a));
-    }
-}
-/// \ingroup CacheManagerInternal
-CacheManager::MenuAction::MenuAction(CacheManager *aMgr) : CacheManagerAction ("menu", "Cache Manager Menu", 0, 1), cmgr(aMgr) { }
-
 /*
  \ingroup CacheManagerInternal
  * gets from the global Config the password the user would need to supply
  * for the action she queried
  */
 char *
