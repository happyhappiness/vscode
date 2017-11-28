bool
UFSStoreState::kickReadQueue()
{
    _queued_read *q = (_queued_read *)linklistShift(&pending_reads);

    if (NULL == q)
        return false;

    debugs(79, 3, "UFSStoreState::kickReadQueue: reading queued request of " << q->size << " bytes");

    void *cbdata;

    if (cbdataReferenceValidDone(q->callback_data, &cbdata)) {
        read_(q->buf, q->size, q->offset, q->callback, cbdata);
    } else {
        debugs(79, 2, "UFSStoreState::kickReadQueue: this: " << this << " cbdataReferenceValidDone returned false." << " closing: " << closing << " flags.try_closing: " << flags.try_closing);
        delete q;
        return false;
    }

    delete q;

    return true;
}