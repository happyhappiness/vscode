uint64_t
Store::Controller::maxSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->maxSize();
}