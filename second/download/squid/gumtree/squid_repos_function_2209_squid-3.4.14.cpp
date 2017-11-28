void
FwdState::Start(const Comm::ConnectionPointer &clientConn, StoreEntry *entry, HttpRequest *request, const AccessLogEntryPointer &al)
{
    /** \note
     * client_addr == no_addr indicates this is an "internal" request
     * from peer_digest.c, asn.c, netdb.c, etc and should always
     * be allowed.  yuck, I know.
     */

    if ( Config.accessList.miss && !request->client_addr.isNoAddr() &&
            request->protocol != AnyP::PROTO_INTERNAL && request->protocol != AnyP::PROTO_CACHE_OBJECT) {
        /**
         * Check if this host is allowed to fetch MISSES from us (miss_access).
         * Intentionally replace the src_addr automatically selected by the checklist code
         * we do NOT want the indirect client address to be tested here.
         */
        ACLFilledChecklist ch(Config.accessList.miss, request, NULL);
        ch.src_addr = request->client_addr;
        if (ch.fastCheck() == ACCESS_DENIED) {
            err_type page_id;
            page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, 1);

            if (page_id == ERR_NONE)
                page_id = ERR_FORWARDING_DENIED;

            ErrorState *anErr = new ErrorState(page_id, Http::scForbidden, request);
            errorAppendEntry(entry, anErr);	// frees anErr
            return;
        }
    }

    debugs(17, 3, HERE << "'" << entry->url() << "'");
    /*
     * This seems like an odd place to bind mem_obj and request.
     * Might want to assert that request is NULL at this point
     */
    entry->mem_obj->request = request;
    HTTPMSGLOCK(entry->mem_obj->request);
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    if (shutting_down) {
        /* more yuck */
        ErrorState *anErr = new ErrorState(ERR_SHUTTING_DOWN, Http::scServiceUnavailable, request);
        errorAppendEntry(entry, anErr);	// frees anErr
        return;
    }

    switch (request->protocol) {

    case AnyP::PROTO_INTERNAL:
        internalStart(clientConn, request, entry);
        return;

    case AnyP::PROTO_CACHE_OBJECT:
        CacheManager::GetInstance()->Start(clientConn, request, entry);
        return;

    case AnyP::PROTO_URN:
        urnStart(request, entry);
        return;

    default:
        FwdState::Pointer fwd = new FwdState(clientConn, entry, request, al);
        fwd->start(fwd);
        return;
    }

    /* NOTREACHED */
}