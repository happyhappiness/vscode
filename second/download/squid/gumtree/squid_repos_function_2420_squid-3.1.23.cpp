int
FwdState::reforward()
{
    StoreEntry *e = entry;
    FwdServer *fs = servers;
    http_status s;
    assert(e->store_status == STORE_PENDING);
    assert(e->mem_obj);
#if URL_CHECKSUM_DEBUG

    e->mem_obj->checkUrlChecksum();
#endif

    debugs(17, 3, "fwdReforward: " << e->url() << "?" );

    if (!EBIT_TEST(e->flags, ENTRY_FWD_HDR_WAIT)) {
        debugs(17, 3, "fwdReforward: No, ENTRY_FWD_HDR_WAIT isn't set");
        return 0;
    }

    if (n_tries > Config.forward_max_tries)
        return 0;

    if (origin_tries > 1)
        return 0;

    if (request->bodyNibbled())
        return 0;

    assert(fs);

    servers = fs->next;

    fwdServerFree(fs);

    if (servers == NULL) {
        debugs(17, 3, "fwdReforward: No forward-servers left");
        return 0;
    }

    s = e->getReply()->sline.status;
    debugs(17, 3, "fwdReforward: status " << s);
    return reforwardableStatus(s);
}