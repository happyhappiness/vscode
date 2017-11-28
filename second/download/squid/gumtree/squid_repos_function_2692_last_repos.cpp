void
internalStart(const Comm::ConnectionPointer &clientConn, HttpRequest * request, StoreEntry * entry)
{
    ErrorState *err;
    const SBuf upath = request->url.path();
    debugs(76, 3, clientConn << " requesting '" << upath << "'");

    static const SBuf netdbUri("/squid-internal-dynamic/netdb");
    static const SBuf storeDigestUri("/squid-internal-periodic/store_digest");
    static const SBuf mgrPfx("/squid-internal-mgr/");

    if (upath == netdbUri) {
        netdbBinaryExchange(entry);
    } else if (upath == storeDigestUri) {
#if USE_CACHE_DIGESTS
        const char *msgbuf = "This cache is currently building its digest.\n";
#else

        const char *msgbuf = "This cache does not support Cache Digests.\n";
#endif

        HttpReply *reply = new HttpReply;
        reply->setHeaders(Http::scNotFound, "Not Found", "text/plain", strlen(msgbuf), squid_curtime, -2);
        entry->replaceHttpReply(reply);
        entry->append(msgbuf, strlen(msgbuf));
        entry->complete();
    } else if (upath.startsWith(mgrPfx)) {
        debugs(17, 2, "calling CacheManager due to URL-path " << mgrPfx);
        CacheManager::GetInstance()->Start(clientConn, request, entry);
    } else {
        debugObj(76, 1, "internalStart: unknown request:\n",
                 request, (ObjPackMethod) & httpRequestPack);
        err = new ErrorState(ERR_INVALID_REQ, Http::scNotFound, request);
        errorAppendEntry(entry, err);
    }
}