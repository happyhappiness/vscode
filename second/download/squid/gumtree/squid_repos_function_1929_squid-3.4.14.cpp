uint64_t
StoreController::minSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->minSize();
}