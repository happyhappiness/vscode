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
        debugs(90, 3, "store_client for " << *e << " has a callback");
        sc->fail();
    }

#if STORE_CLIENT_LIST_DEBUG
    cbdataReferenceDone(sc->owner);

#endif

    delete sc;

    assert(e->locked());
    // An entry locked by others may be unlocked (and destructed) by others, so
    // we must lock again to safely dereference e after CheckQuickAbortIsReasonable().
    e->lock("storeUnregister");

    if (CheckQuickAbortIsReasonable(e))
        e->abort();
    else
        mem->kickReads();

#if USE_ADAPTATION
    e->kickProducer();
#endif

    e->unlock("storeUnregister");
    return 1;
}