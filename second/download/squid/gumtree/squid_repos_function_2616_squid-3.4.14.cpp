HttpReply *
FtpStateData::ftpAuthRequired(HttpRequest * request, const char *realm)
{
    ErrorState err(ERR_CACHE_ACCESS_DENIED, Http::scUnauthorized, request);
    HttpReply *newrep = err.BuildHttpReply();
#if HAVE_AUTH_MODULE_BASIC
    /* add Authenticate header */
    newrep->header.putAuth("Basic", realm);
#endif
    return newrep;
}