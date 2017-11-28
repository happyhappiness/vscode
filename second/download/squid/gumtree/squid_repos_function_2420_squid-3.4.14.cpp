int
storeUnregister(store_client * sc, StoreEntry * e, void *data)
{
    MemObject *mem = e->mem_obj;
#if STORE_CLIENT_LIST_DEBUG

    assert(sc == storeClientListSearch(e->mem_obj, data));
#endif

    if (mem == NULL)
        return 0;

    debugs(90, 3, "storeUnregister: called for '" << e->getMD5Text() << "'");

    if (sc == NULL) {
        debugs(90, 3, "storeUnregister: No matching client for '" << e->getMD5Text() << "'");
        return 0;
    }

    if (mem->clientCount() == 0) {
        debugs(90, 3, "storeUnregister: Consistency failure - store client being unregistered is not in the mem object's list for '" << e->getMD5Text() << "'");
        return 0;
    }

    dlinkDelete(&sc->node, &mem->clients);
    -- mem->nclients;

    if (e->store_status == STORE_OK && e->swap_status != SWAPOUT_DONE)
        e->swapOut();

    if (sc->swapin_sio != NULL) {
        storeClose(sc->swapin_sio, StoreIOState::readerDone);
        sc->swapin_sio = NULL;
        ++statCounter.swap.ins;
    }

    if (sc->_callback.pending()) {
        /* callback with ssize = -1 to indicate unexpected termination */
        debugs(90, 3, "storeUnregister: store_client for " << mem->url << " has a callback");
        sc->fail();
    }

#if STORE_CLIENT_LIST_DEBUG
    cbdataReferenceDone(sc->owner);

#endif

    delete sc;

    // This old assert seemed to imply that a locked entry cannot be deleted,
    // but this entry may be deleted because StoreEntry::abort() unlocks it.
    assert(e->lock_count > 0);
    // Since lock_count of 1 is not sufficient to prevent entry destruction,
    // we must lock again so that we can dereference e after CheckQuickAbort().
    // Do not call expensive StoreEntry::lock() here; e "use" has been counted.
    // TODO: Separate entry locking from "use" counting to make locking cheap.
    ++e->lock_count;

    if (mem->nclients == 0)
        CheckQuickAbort(e);
    else
        mem->kickReads();

#if USE_ADAPTATION
    e->kickProducer();
#endif

    e->unlock(); // after the "++e->lock_count" above
    return 1;
}