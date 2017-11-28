void
FwdState::fwdStart(int client_fd, StoreEntry *entry, HttpRequest *request)
{
    /** \note
     * client_addr == no_addr indicates this is an "internal" request
     * from peer_digest.c, asn.c, netdb.c, etc and should always
     * be allowed.  yuck, I know.
     */

    if ( Config.accessList.miss && !request->client_addr.IsNoAddr() &&
            request->protocol != PROTO_INTERNAL && request->protocol != PROTO_CACHEOBJ) {
        /**
         * Check if this host is allowed to fetch MISSES from us (miss_access)
         */
        ACLFilledChecklist ch(Config.accessList.miss, request, NULL);
        ch.src_addr = request->client_addr;
        ch.my_addr = request->my_addr;
        int answer = ch.fastCheck();

        if (answer == 0) {
            err_type page_id;
            page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, 1);

            if (page_id == ERR_NONE)
                page_id = ERR_FORWARDING_DENIED;

            ErrorState *anErr = errorCon(page_id, HTTP_FORBIDDEN, request);

            errorAppendEntry(entry, anErr);	// frees anErr

            return;
        }
    }

    debugs(17, 3, "FwdState::start() '" << entry->url() << "'");
    /*
     * This seems like an odd place to bind mem_obj and request.
     * Might want to assert that request is NULL at this point
     */
    entry->mem_obj->request = HTTPMSGLOCK(request);
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    if (shutting_down) {
        /* more yuck */
        ErrorState *anErr = errorCon(ERR_SHUTTING_DOWN, HTTP_SERVICE_UNAVAILABLE, request);
        errorAppendEntry(entry, anErr);	// frees anErr
        return;
    }

    switch (request->protocol) {

    case PROTO_INTERNAL:
        internalStart(request, entry);
        return;

    case PROTO_CACHEOBJ:
        CacheManager::GetInstance()->Start(client_fd, request, entry);
        return;

    case PROTO_URN:
        urnStart(request, entry);
        return;

    default:
        FwdState::Pointer fwd = new FwdState(client_fd, entry, request);

        /* If we need to transparently proxy the request
         * then we need the client source protocol, address and port */
        if (request->flags.spoof_client_ip) {
            fwd->src = request->client_addr;
        }

        fwd->start(fwd);
        return;
    }

    /* NOTREACHED */
}