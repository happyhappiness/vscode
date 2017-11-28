uint64_t
Store::Controller::currentSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->currentSize();
}