void
Fs::Ufs::UFSStoreState::doWrite()
{
    debugs(79, 3, (void*)this);

    assert(theFile->canWrite());

    if (pending_writes.empty()) {
        debugs(79, 3, (void*)this << " write queue is empty");
        return;
    }

    auto &q = pending_writes.front();

    if (theFile->error()) {
        debugs(79, DBG_IMPORTANT, MYNAME << " avoid write on theFile with error");
        pending_writes.pop();
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
    debugs(79, 3, (void*)this << " calling theFile->write(" << q.size << ")");

    theFile->write(new WriteRequest(q.buf, q.offset, q.size, q.free_func));
    q.buf = nullptr; // prevent buf deletion on pop, its used by the above object
    pending_writes.pop();
}