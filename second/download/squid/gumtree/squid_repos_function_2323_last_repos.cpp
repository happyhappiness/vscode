void
CacheManager::ParseHeaders(const HttpRequest * request, Mgr::ActionParams &params)
{
    assert(request);

    params.httpMethod = request->method.id();
    params.httpFlags = request->flags;

#if HAVE_AUTH_MODULE_BASIC
    // TODO: use the authentication system decode to retrieve these details properly.

    /* base 64 _decoded_ user:passwd pair */
    const char *basic_cookie = request->header.getAuth(Http::HdrType::AUTHORIZATION, "Basic");

    if (!basic_cookie)
        return;

    const char *passwd_del;
    if (!(passwd_del = strchr(basic_cookie, ':'))) {
        debugs(16, DBG_IMPORTANT, "CacheManager::ParseHeaders: unknown basic_cookie format '" << basic_cookie << "'");
        return;
    }

    /* found user:password pair, reset old values */
    params.userName.limitInit(basic_cookie, passwd_del - basic_cookie);
    params.password = passwd_del + 1;

    /* warning: this prints decoded password which maybe not be what you want to do @?@ @?@ */
    debugs(16, 9, "CacheManager::ParseHeaders: got user: '" <<
           params.userName << "' passwd: '" << params.password << "'");
#endif
}