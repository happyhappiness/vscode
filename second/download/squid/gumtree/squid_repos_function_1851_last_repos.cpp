int
FwdState::reforward()
{
    StoreEntry *e = entry;

    if (EBIT_TEST(e->flags, ENTRY_ABORTED)) {
        debugs(17, 3, HERE << "entry aborted");
        return 0;
    }

    assert(e->store_status == STORE_PENDING);
    assert(e->mem_obj);
#if URL_CHECKSUM_DEBUG

    e->mem_obj->checkUrlChecksum();
#endif

    debugs(17, 3, HERE << e->url() << "?" );

    if (!EBIT_TEST(e->flags, ENTRY_FWD_HDR_WAIT)) {
        debugs(17, 3, HERE << "No, ENTRY_FWD_HDR_WAIT isn't set");
        return 0;
    }

    if (n_tries > Config.forward_max_tries)
        return 0;

    if (request->bodyNibbled())
        return 0;

    if (serverDestinations.size() <= 1) {
        // NP: <= 1 since total count includes the recently failed one.
        debugs(17, 3, HERE << "No alternative forwarding paths left");
        return 0;
    }

    const Http::StatusCode s = e->getReply()->sline.status();
    debugs(17, 3, HERE << "status " << s);
    return reforwardableStatus(s);
}