HttpReply *
Ftp::Gateway::ftpAuthRequired(HttpRequest * request, SBuf &realm)
{
    ErrorState err(ERR_CACHE_ACCESS_DENIED, Http::scUnauthorized, request);
    HttpReply *newrep = err.BuildHttpReply();
#if HAVE_AUTH_MODULE_BASIC
    /* add Authenticate header */
    // XXX: performance regression. c_str() may reallocate
    newrep->header.putAuth("Basic", realm.c_str());
#endif
    return newrep;
}