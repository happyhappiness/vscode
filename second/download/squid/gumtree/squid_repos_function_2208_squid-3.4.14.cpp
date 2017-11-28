void
FwdState::completed()
{
    if (flags.forward_completed) {
        debugs(17, DBG_IMPORTANT, HERE << "FwdState::completed called on a completed request! Bad!");
        return;
    }

    flags.forward_completed = true;

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        debugs(17, 3, HERE << "entry aborted");
        return ;
    }

#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    if (entry->store_status == STORE_PENDING) {
        if (entry->isEmpty()) {
            if (!err) // we quit (e.g., fd closed) before an error or content
                fail(new ErrorState(ERR_READ_ERROR, Http::scBadGateway, request));
            assert(err);
            errorAppendEntry(entry, err);
            err = NULL;
#if USE_SSL
            if (request->flags.sslPeek && request->clientConnectionManager.valid()) {
                CallJobHere1(17, 4, request->clientConnectionManager, ConnStateData,
                             ConnStateData::httpsPeeked, Comm::ConnectionPointer(NULL));
            }
#endif
        } else {
            EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
            entry->complete();
            entry->releaseRequest();
        }
    }

    if (storePendingNClients(entry) > 0)
        assert(!EBIT_TEST(entry->flags, ENTRY_FWD_HDR_WAIT));

}