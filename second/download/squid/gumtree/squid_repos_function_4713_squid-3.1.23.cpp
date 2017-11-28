void
UFSStoreState::queueRead(char *buf, size_t size, off_t aOffset, STRCB *callback_, void *callback_data_)
{
    debugs(79, 3, "UFSStoreState::queueRead: queueing read");
    assert(opening);
    assert (pending_reads == NULL);
    _queued_read *q = new _queued_read;
    q->buf = buf;
    q->size = size;
    q->offset = aOffset;
    q->callback = callback_;
    q->callback_data = cbdataReference(callback_data_);
    linklistPush(&pending_reads, q);
}