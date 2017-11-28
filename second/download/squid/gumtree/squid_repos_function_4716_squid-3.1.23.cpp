void
UFSStoreState::queueWrite(char const *buf, size_t size, off_t aOffset, FREE * free_func)
{
    debugs(79, 3, HERE << this << " UFSStoreState::queueWrite: queueing write of size " << size);

    _queued_write *q;
    q = new _queued_write;
    q->buf = buf;
    q->size = size;
    q->offset = aOffset;
    q->free_func = free_func;
    linklistPush(&pending_writes, q);
}