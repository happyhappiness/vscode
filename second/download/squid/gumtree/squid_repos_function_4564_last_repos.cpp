uint64_t
Store::Controller::currentCount() const
{
    /* TODO: include memory cache ? */
    return swapDir->currentCount();
}