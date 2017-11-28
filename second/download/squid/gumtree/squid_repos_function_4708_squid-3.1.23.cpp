void
UFSStoreState::readCompleted(const char *buf, int len, int errflag, RefCount<ReadRequest> result)
{
    assert (result.getRaw());
    reading = false;
    debugs(79, 3, "UFSStoreState::readCompleted: dirno " << swap_dirn  <<
           ", fileno "<< std::setfill('0') << std::hex << std::setw(8) <<
           swap_filen  << " len "<< std::setfill(' ') << std::dec << len);

    if (len > 0)
        offset_ += len;

    STRCB *callback_ = read.callback;

    assert(callback_);

    read.callback = NULL;

    void *cbdata;

    /* A note:
     * diskd IO queues closes via the diskd queue. So close callbacks
     * occur strictly after reads and writes.
     * ufs doesn't queue, it simply completes, so close callbacks occur
     * strictly after reads and writes.
     * aufs performs closes syncronously, so close events must be managed
     * to force strict ordering.
     * The below does this:
     * closing is set when theFile->close() has been called, and close only triggers
     * when no io's are pending.
     * writeCompleted likewise.
     */
    if (!closing && cbdataReferenceValidDone(read.callback_data, &cbdata)) {
        if (len > 0 && read_buf != buf)
            memcpy(read_buf, buf, len);

        callback_(cbdata, read_buf, len, this);
    }

    if (flags.try_closing || (theFile != NULL && theFile->error()) )
        tryClosing();
}