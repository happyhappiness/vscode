bool
Store::Controller::smpAware() const
{
    return memStore || (swapDir && swapDir->smpAware());
}