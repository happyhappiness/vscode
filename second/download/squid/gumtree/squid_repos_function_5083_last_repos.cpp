bool
Fs::Ufs::UFSStoreState::kickReadQueue()
{
    if (pending_reads.empty())
        return false;

    auto &q = pending_reads.front();

    debugs(79, 3, "reading queued request of " << q.size << " bytes");

    bool result = true;
    void *cbdata;
    if (cbdataReferenceValidDone(q.callback_data, &cbdata)) {
        read_(q.buf, q.size, q.offset, q.callback, cbdata);
    } else {
        debugs(79, 2, "this=" << (void*)this << " cbdataReferenceValidDone returned false." <<
               " closing: " << closing << " flags.try_closing: " << flags.try_closing);
        result = false;
    }

    pending_reads.pop(); // erase the front object
    return result;
}