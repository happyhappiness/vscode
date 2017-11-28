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