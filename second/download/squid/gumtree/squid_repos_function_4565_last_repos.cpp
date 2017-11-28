int64_t
Store::Controller::maxObjectSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->maxObjectSize();
}