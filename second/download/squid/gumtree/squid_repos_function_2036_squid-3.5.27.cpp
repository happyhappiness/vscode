uint64_t
StoreController::maxSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->maxSize();
}