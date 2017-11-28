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