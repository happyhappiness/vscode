SBuf::size_type
SBuf::reserve(const SBufReservationRequirements &req)
{
    debugs(24, 8, id << " was: " << off_ << '+' << len_ << '+' << spaceSize() <<
           '=' << store_->capacity);

    const bool mustRealloc = !req.allowShared && store_->LockCount() > 1;

    if (!mustRealloc && spaceSize() >= req.minSpace)
        return spaceSize(); // the caller is content with what we have

    /* only reallocation can make the caller happy */

    if (!mustRealloc && len_ >= req.maxCapacity)
        return spaceSize(); // but we cannot reallocate

    const size_type desiredSpace = std::max(req.minSpace, req.idealSpace);
    const size_type newSpace = std::min(desiredSpace, maxSize - len_);
    reserveCapacity(std::min(len_ + newSpace, req.maxCapacity));
    debugs(24, 7, id << " now: " << off_ << '+' << len_ << '+' << spaceSize() <<
           '=' << store_->capacity);
    return spaceSize(); // reallocated and probably reserved enough space
}