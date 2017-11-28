void
SBuf::reAlloc(size_type newsize)
{
    debugs(24, 8, id << " new size: " << newsize);
    if (newsize > maxSize)
        throw SBufTooBigException(__FILE__, __LINE__);
    MemBlob::Pointer newbuf = new MemBlob(newsize);
    if (length() > 0)
        newbuf->append(buf(), length());
    store_ = newbuf;
    off_ = 0;
    ++stats.cowSlow;
    debugs(24, 7, id << " new store capacity: " << store_->capacity);
}