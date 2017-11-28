void
Fs::Ufs::UFSStoreState::doWrite()
{
    debugs(79, 3, HERE << this << " UFSStoreState::doWrite");

    assert(theFile->canWrite());

    _queued_write *q = (_queued_write *)linklistShift(&pending_writes);

    if (q == NULL) {
        debugs(79, 3, HERE << this << " UFSStoreState::doWrite queue is empty");
        return;
    }

    if (theFile->error()) {
        debugs(79, DBG_IMPORTANT,HERE << "avoid write on theFile with error");
        debugs(79,3,HERE << "calling free_func for " << (void*) q->buf);
        /*
         * DPW 2006-05-24
         * Note "free_func" is memNodeWriteComplete(), which doesn't
         * really free the memory.  Instead it clears the node's
         * write_pending flag.
         */
        q->free_func((void*)q->buf);
        delete q;
        return;
    }

    /*
     * DPW 2006-05-24
     * UFSStoreState has a 'writing' flag that we used to set here,
     * but it wasn't really used anywhere.  In fact, some lower
     * layers such as DISKD allow multiple outstanding writes, which
     * makes the boolean writing flag meaningless.  We would need
     * a counter to keep track of writes going out and write callbacks
     * coming in.  For now let's just not use the writing flag at
     * all.
     */
    debugs(79, 3, HERE << this << " calling theFile->write(" << q->size << ")");

    theFile->write(new WriteRequest(q->buf, q->offset, q->size, q->free_func));
    delete q;
}