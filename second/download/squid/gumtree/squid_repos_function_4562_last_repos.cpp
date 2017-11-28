uint64_t
Store::Controller::minSize() const
{
    /* TODO: include memory cache ? */
    return swapDir->minSize();
}