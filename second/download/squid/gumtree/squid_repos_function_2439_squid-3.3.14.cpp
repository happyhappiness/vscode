void
FwdState::complete()
{
    debugs(17, 3, HERE << entry->url() << "\n\tstatus " << entry->getReply()->sline.status  );
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    logReplyStatus(n_tries, entry->getReply()->sline.status);

    if (reforward()) {
        debugs(17, 3, HERE << "re-forwarding " << entry->getReply()->sline.status << " " << entry->url());

        if (Comm::IsConnOpen(serverConn))
            unregister(serverConn);

        entry->reset();

        // drop the last path off the selection list. try the next one.
        serverDestinations.shift();
        startConnectionOrFail();

    } else {
        if (Comm::IsConnOpen(serverConn))
            debugs(17, 3, HERE << "server FD " << serverConnection()->fd << " not re-forwarding status " << entry->getReply()->sline.status);
        else
            debugs(17, 3, HERE << "server (FD closed) not re-forwarding status " << entry->getReply()->sline.status);
        EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
        entry->complete();

        if (!Comm::IsConnOpen(serverConn))
            completed();

        self = NULL; // refcounted
    }
}