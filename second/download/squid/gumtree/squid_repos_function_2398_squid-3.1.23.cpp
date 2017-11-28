void
FwdState::complete()
{
    StoreEntry *e = entry;
    assert(entry->store_status == STORE_PENDING);
    debugs(17, 3, HERE << e->url() << "\n\tstatus " << entry->getReply()->sline.status  );
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    logReplyStatus(n_tries, entry->getReply()->sline.status);

    if (reforward()) {
        debugs(17, 3, "fwdComplete: re-forwarding " << entry->getReply()->sline.status << " " << e->url());

        if (server_fd > -1)
            unregister(server_fd);

        e->reset();

        startComplete(servers);
    } else {
        debugs(17, 3, "fwdComplete: server FD " << server_fd << " not re-forwarding status " << entry->getReply()->sline.status);
        EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
        entry->complete();

        if (server_fd < 0)
            completed();

        self = NULL; // refcounted
    }
}