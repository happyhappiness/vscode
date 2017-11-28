void
UFSStoreState::doCloseCallback(int errflag)
{
    debugs(79, 3, "storeUfsIOCallback: errflag=" << errflag);
    /*
     * DPW 2006-05-24
     * When we signal the higher layer with this callback, it might unlock
     * the StoreEntry and its associated data.  We must "free" any queued
     * I/Os (especially writes) now, otherwise the StoreEntry's mem_node's
     * will have their write_pending flag set, and we'll get an assertion.
     */
    freePending();
    STIOCB *theCallback = callback;
    callback = NULL;

    void *cbdata;

    if (cbdataReferenceValidDone(callback_data, &cbdata) && theCallback)
        theCallback(cbdata, errflag, this);

    /*
     * We are finished with theFile since the lower layer signalled
     * us that the file has been closed.  This must be the last line,
     * as theFile may be the only object holding us in memory.
     */
    theFile = NULL;	// refcounted
}