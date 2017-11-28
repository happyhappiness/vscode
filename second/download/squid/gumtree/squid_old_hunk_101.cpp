/**
 \ingroup CacheManagerInternal
 * Locates an action in the actions registry ActionsList.
\retval NULL  if Action not found
\retval CacheManagerAction* if the action was found
 */
CacheManagerAction *
CacheManager::findAction(char const * action)
{
    CacheManagerActionList::iterator a;

    debugs(16, 5, "CacheManager::findAction: looking for action " << action);
    for ( a = ActionsList.begin(); a != ActionsList.end(); a++) {
        if (0 == strcmp((*a)->action, action)) {
            debugs(16, 6, " found");
            return *a;
        }
    }

    debugs(16, 6, "Action not found.");
    return NULL;
}

/**
 \ingroup CacheManagerInternal
 * define whether the URL is a cache-manager URL and parse the action
 * requested by the user. Checks via CacheManager::ActionProtection() that the
 * item is accessible by the user.
 \retval CacheManager::cachemgrStateData state object for the following handling
 \retval NULL if the action can't be found or can't be accessed by the user
 */
CacheManager::cachemgrStateData *
CacheManager::ParseUrl(const char *url)
{
    int t;
    LOCAL_ARRAY(char, host, MAX_URL);
    LOCAL_ARRAY(char, request, MAX_URL);
    LOCAL_ARRAY(char, password, MAX_URL);
    CacheManagerAction *a;
    cachemgrStateData *mgr = NULL;
    const char *prot;
    t = sscanf(url, "cache_object://%[^/]/%[^@]@%s", host, request, password);

    if (t < 2) {
        xstrncpy(request, "menu", MAX_URL);
#ifdef _SQUID_OS2_
        /*
         * emx's sscanf insists of returning 2 because it sets request
         * to null
         */
    } else if (request[0] == '\0') {
        xstrncpy(request, "menu", MAX_URL);
#endif

    } else if ((a = findAction(request)) == NULL) {
        debugs(16, DBG_IMPORTANT, "CacheManager::ParseUrl: action '" << request << "' not found");
        return NULL;
    } else {
        prot = ActionProtection(a);

        if (!strcmp(prot, "disabled") || !strcmp(prot, "hidden")) {
            debugs(16, DBG_IMPORTANT, "CacheManager::ParseUrl: action '" << request << "' is " << prot);
            return NULL;
        }
    }

    /* set absent entries to NULL so we can test if they are present later */
    mgr = (cachemgrStateData *)xcalloc(1, sizeof(cachemgrStateData));

    mgr->user_name = NULL;

    mgr->passwd = t == 3 ? xstrdup(password) : NULL;

    mgr->action = xstrdup(request);

    return mgr;
}

/// \ingroup CacheManagerInternal
/*
 \ingroup CacheManagerInternal
 * Decodes the headers needed to perform user authentication and fills
 * the details into the cachemgrStateData argument
 */
void
CacheManager::ParseHeaders(cachemgrStateData * mgr, const HttpRequest * request)
{
    const char *basic_cookie;	/* base 64 _decoded_ user:passwd pair */
    const char *passwd_del;
    assert(mgr && request);
    basic_cookie = request->header.getAuth(HDR_AUTHORIZATION, "Basic");

    if (!basic_cookie)
        return;

    if (!(passwd_del = strchr(basic_cookie, ':'))) {
        debugs(16, DBG_IMPORTANT, "CacheManager::ParseHeaders: unknown basic_cookie format '" << basic_cookie << "'");
        return;
    }

    /* found user:password pair, reset old values */
    safe_free(mgr->user_name);

    safe_free(mgr->passwd);

    mgr->user_name = xstrdup(basic_cookie);

    mgr->user_name[passwd_del - basic_cookie] = '\0';

    mgr->passwd = xstrdup(passwd_del + 1);

    /* warning: this prints decoded password which maybe not what you want to do @?@ @?@ */
    debugs(16, 9, "CacheManager::ParseHeaders: got user: '" << mgr->user_name << "' passwd: '" << mgr->passwd << "'");
}

/**
 \ingroup CacheManagerInternal
 *
 \retval 0	if mgr->password is good or "none"
 \retval 1	if mgr->password is "disable"
 \retval !0	if mgr->password does not match configured password
 */
int
CacheManager::CheckPassword(cachemgrStateData * mgr)
{
    char *pwd = PasswdGet(Config.passwd_list, mgr->action);
    CacheManagerAction *a = findAction(mgr->action);

    debugs(16, 4, "CacheManager::CheckPassword for action " << mgr->action);
    assert(a != NULL);

    if (pwd == NULL)
        return a->flags.pw_req;

    if (strcmp(pwd, "disable") == 0)
        return 1;

    if (strcmp(pwd, "none") == 0)
        return 0;

    if (!mgr->passwd)
        return 1;

    return strcmp(pwd, mgr->passwd);
}

/// \ingroup CacheManagerInternal
void
CacheManager::StateFree(cachemgrStateData * mgr)
{
    safe_free(mgr->action);
    safe_free(mgr->user_name);
    safe_free(mgr->passwd);
    mgr->entry->unlock();
    xfree(mgr);
}

/**
 \ingroup CacheManagerAPI
 * Main entry point in the Cache Manager's activity. Gets called as part
 * of the forward chain if the right URL is detected there. Initiates
 * all needed internal work and renders the response.
 */
void
CacheManager::Start(int fd, HttpRequest * request, StoreEntry * entry)
{
    cachemgrStateData *mgr = NULL;
    ErrorState *err = NULL;
    CacheManagerAction *a;
    debugs(16, 3, "CacheManager::Start: '" << entry->url() << "'" );

    if ((mgr = ParseUrl(entry->url())) == NULL) {
        err = errorCon(ERR_INVALID_URL, HTTP_NOT_FOUND, request);
        err->url = xstrdup(entry->url());
        errorAppendEntry(entry, err);
        entry->expires = squid_curtime;
        return;
    }

    mgr->entry = entry;

    entry->lock();
    entry->expires = squid_curtime;

    debugs(16, 5, "CacheManager: " << fd_table[fd].ipaddr << " requesting '" << mgr->action << "'");

    /* get additional info from request headers */
    ParseHeaders(mgr, request);

    /* Check password */

    if (CheckPassword(mgr) != 0) {
        /* build error message */
        ErrorState *errState;
        HttpReply *rep;
        errState = errorCon(ERR_CACHE_MGR_ACCESS_DENIED, HTTP_UNAUTHORIZED, request);
        /* warn if user specified incorrect password */

        if (mgr->passwd)
            debugs(16, DBG_IMPORTANT, "CacheManager: " <<
                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
                   fd_table[fd].ipaddr << ": incorrect password for '" <<
                   mgr->action << "'" );
        else
            debugs(16, DBG_IMPORTANT, "CacheManager: " <<
                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
                   fd_table[fd].ipaddr << ": password needed for '" <<
                   mgr->action << "'" );

        rep = errState->BuildHttpReply();

        errorStateFree(errState);

        /*
         * add Authenticate header, use 'action' as a realm because
         * password depends on action
         */
        rep->header.putAuth("Basic", mgr->action);

        /* store the reply */
        entry->replaceHttpReply(rep);

        entry->expires = squid_curtime;

        entry->complete();

        StateFree(mgr);

        return;
    }

    debugs(16, 2, "CacheManager: " <<
           (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
           fd_table[fd].ipaddr << " requesting '" <<
           mgr->action << "'" );
    /* retrieve object requested */
    a = findAction(mgr->action);
    assert(a != NULL);

    entry->buffer();

    {
        HttpReply *rep = new HttpReply;
        rep->setHeaders(HTTP_OK, NULL, "text/plain", -1, squid_curtime, squid_curtime);
        entry->replaceHttpReply(rep);
    }

    a->run(entry);

    entry->flush();

    if (a->flags.atomic)
        entry->complete();

    StateFree(mgr);
}

/// \ingroup CacheManagerInternal
void CacheManager::ShutdownAction::run(StoreEntry *sentry)
{
    debugs(16, DBG_CRITICAL, "Shutdown by Cache Manager command.");
    shut_down(0);
}
/// \ingroup CacheManagerInternal
CacheManager::ShutdownAction::ShutdownAction() : CacheManagerAction("shutdown","Shut Down the Squid Process", 1, 1) { }

/// \ingroup CacheManagerInternal
void
CacheManager::ReconfigureAction::run(StoreEntry * sentry)
{
    debugs(16, DBG_IMPORTANT, "Reconfigure by Cache Manager command.");
    storeAppendPrintf(sentry, "Reconfiguring Squid Process ....");
    reconfigure(SIGHUP);
}
/// \ingroup CacheManagerInternal
CacheManager::ReconfigureAction::ReconfigureAction() : CacheManagerAction("reconfigure","Reconfigure Squid", 1, 1) { }

/// \ingroup CacheManagerInternal
void
CacheManager::OfflineToggleAction::run(StoreEntry * sentry)
{
    Config.onoff.offline = !Config.onoff.offline;
    debugs(16, DBG_IMPORTANT, "offline_mode now " << (Config.onoff.offline ? "ON" : "OFF") << " by Cache Manager request.");

    storeAppendPrintf(sentry, "offline_mode is now %s\n",
                      Config.onoff.offline ? "ON" : "OFF");
}
/// \ingroup CacheManagerInternal
CacheManager::OfflineToggleAction::OfflineToggleAction() : CacheManagerAction ("offline_toggle", "Toggle offline_mode setting", 1, 1) { }

/*
 \ingroup CacheManagerInternal
 * Renders the protection level text for an action.
 * Also doubles as a check for the protection level.
 */
const char *
CacheManager::ActionProtection(const CacheManagerAction * at)
{
    char *pwd;
    assert(at);
    pwd = PasswdGet(Config.passwd_list, at->action);

    if (!pwd)
        return at->flags.pw_req ? "hidden" : "public";

    if (!strcmp(pwd, "disable"))
        return "disabled";

    if (strcmp(pwd, "none") == 0)
        return "public";

    return "protected";
}

/// \ingroup CacheManagerInternal
void
CacheManager::MenuAction::run(StoreEntry * sentry)
{
    CacheManagerActionList::iterator a;

    debugs(16, 4, "CacheManager::MenuCommand invoked");
    for (a = cmgr->ActionsList.begin(); a != cmgr->ActionsList.end(); ++a) {
        debugs(16, 5, "  showing action " << (*a)->action);
        storeAppendPrintf(sentry, " %-22s\t%-32s\t%s\n",
                          (*a)->action, (*a)->desc, cmgr->ActionProtection(*a));
    }
}
/// \ingroup CacheManagerInternal
CacheManager::MenuAction::MenuAction(CacheManager *aMgr) : CacheManagerAction ("menu", "Cache Manager Menu", 0, 1), cmgr(aMgr) { }

/*
 \ingroup CacheManagerInternal
 * gets from the global Config the password the user would need to supply
 * for the action she queried
 */
char *
