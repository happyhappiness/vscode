void
SBuf::forceSize(size_type newSize)
{
    debugs(24, 8, id << " force " << (newSize > length() ? "grow" : "shrink") << " to length=" << newSize);

    Must(store_->LockCount() == 1);
    if (newSize > min(maxSize,store_->capacity-off_))
        throw SBufTooBigException(__FILE__,__LINE__);
    len_ = newSize;
    store_->size = newSize;
}