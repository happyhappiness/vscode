void
Mgr::Action::fillEntry(StoreEntry* entry, bool writeHttpHeader)
{
    debugs(16, 5, HERE);
    entry->buffer();

    if (writeHttpHeader) {
        HttpReply *rep = new HttpReply;
        rep->setHeaders(Http::scOkay, NULL, "text/plain", -1, squid_curtime, squid_curtime);
        // Allow cachemgr and other XHR scripts access to our version string
        const ActionParams &params = command().params;
        if (params.httpOrigin.size() > 0) {
            rep->header.putExt("Access-Control-Allow-Origin", params.httpOrigin.termedBuf());
#if HAVE_AUTH_MODULE_BASIC
            rep->header.putExt("Access-Control-Allow-Credentials","true");
#endif
            rep->header.putExt("Access-Control-Expose-Headers","Server");
        }
        entry->replaceHttpReply(rep);
    }

    dump(entry);

    entry->flush();

    if (atomic())
        entry->complete();
}