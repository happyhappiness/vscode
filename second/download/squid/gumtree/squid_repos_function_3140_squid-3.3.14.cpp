void
errorAppendEntry(StoreEntry * entry, ErrorState * err)
{
    assert(entry->mem_obj != NULL);
    assert (entry->isEmpty());
    debugs(4, 4, "Creating an error page for entry " << entry <<
           " with errorstate " << err <<
           " page id " << err->page_id);

    if (entry->store_status != STORE_PENDING) {
        debugs(4, 2, "Skipping error page due to store_status: " << entry->store_status);
        /*
         * If the entry is not STORE_PENDING, then no clients
         * care about it, and we don't need to generate an
         * error message
         */
        assert(EBIT_TEST(entry->flags, ENTRY_ABORTED));
        assert(entry->mem_obj->nclients == 0);
        delete err;
        return;
    }

    if (err->page_id == TCP_RESET) {
        if (err->request) {
            debugs(4, 2, "RSTing this reply");
            err->request->flags.resetTcp=true;
        }
    }

    entry->lock();
    entry->buffer();
    entry->replaceHttpReply( err->BuildHttpReply() );
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    entry->flush();
    entry->complete();
    entry->negativeCache();
    entry->releaseRequest();
    entry->unlock();
    delete err;
}