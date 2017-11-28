void
FwdState::completed()
{
    if (flags.forward_completed == 1) {
        debugs(17, 1, HERE << "FwdState::completed called on a completed request! Bad!");
        return;
    }

    flags.forward_completed = 1;

#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif
#if WIP_FWD_LOG

    log();
#endif

    if (entry->store_status == STORE_PENDING) {
        if (entry->isEmpty()) {
            assert(err);
            errorAppendEntry(entry, err);
            err = NULL;
        } else {
            EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
            entry->complete();
            entry->releaseRequest();
        }
    }

    if (storePendingNClients(entry) > 0)
        assert(!EBIT_TEST(entry->flags, ENTRY_FWD_HDR_WAIT));

}