void
StoreEntry::abort()
{
    statCounter.aborted_requests++;
    assert(store_status == STORE_PENDING);
    assert(mem_obj != NULL);
    debugs(20, 6, "storeAbort: " << getMD5Text());

    lock();         /* lock while aborting */
    negativeCache();

    releaseRequest();

    EBIT_SET(flags, ENTRY_ABORTED);

    setMemStatus(NOT_IN_MEMORY);

    store_status = STORE_OK;

    /*
     * We assign an object length here.  The only other place we assign
     * the object length is in storeComplete()
     */
    /* RBC: What do we need an object length for? we've just aborted the
     * request, the request is private and negatively cached. Surely
     * the object length is inappropriate to set.
     */
    mem_obj->object_sz = mem_obj->endOffset();

    /* Notify the server side */

    /*
     * DPW 2007-05-07
     * Should we check abort.data for validity?
     */
    if (mem_obj->abort.callback) {
        if (!cbdataReferenceValid(mem_obj->abort.data))
            debugs(20,1,HERE << "queueing event when abort.data is not valid");
        eventAdd("mem_obj->abort.callback",
                 mem_obj->abort.callback,
                 mem_obj->abort.data,
                 0.0,
                 true);
        unregisterAbort();
    }

    /* XXX Should we reverse these two, so that there is no
     * unneeded disk swapping triggered?
     */
    /* Notify the client side */
    invokeHandlers();

    /* Close any swapout file */
    swapOutFileClose();

    unlock();       /* unlock */
}