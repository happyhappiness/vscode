bool
StoreController::smpAware() const
{
    return memStore || (swapDir.getRaw() && swapDir->smpAware());
}