void
internalStart(HttpRequest * request, StoreEntry * entry)
{
    ErrorState *err;
    const char *upath = request->urlpath.termedBuf();
    debugs(76, 3, "internalStart: " << request->client_addr << " requesting '" << upath << "'");

    if (0 == strcmp(upath, "/squid-internal-dynamic/netdb")) {
        netdbBinaryExchange(entry);
    } else if (0 == strcmp(upath, "/squid-internal-periodic/store_digest")) {
#if USE_CACHE_DIGESTS
        const char *msgbuf = "This cache is currently building its digest.\n";
#else

        const char *msgbuf = "This cache does not support Cache Digests.\n";
#endif

        HttpReply *reply = new HttpReply;
        reply->setHeaders(HTTP_NOT_FOUND, "Not Found", "text/plain", strlen(msgbuf), squid_curtime, -2);
        entry->replaceHttpReply(reply);
        entry->append(msgbuf, strlen(msgbuf));
        entry->complete();
    } else {
        debugObj(76, 1, "internalStart: unknown request:\n",
                 request, (ObjPackMethod) & httpRequestPack);
        err = errorCon(ERR_INVALID_REQ, HTTP_NOT_FOUND, request);
        errorAppendEntry(entry, err);
    }
}