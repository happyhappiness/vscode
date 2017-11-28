HttpReply *
FtpStateData::ftpAuthRequired(HttpRequest * request, const char *realm)
{
    ErrorState *err = errorCon(ERR_CACHE_ACCESS_DENIED, HTTP_UNAUTHORIZED, request);
    HttpReply *newrep = err->BuildHttpReply();
    errorStateFree(err);
    /* add Authenticate header */
    newrep->header.putAuth("Basic", realm);
    return newrep;
}