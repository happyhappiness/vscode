void
Fs::Ufs::StoreSearchUFS::next(void (aCallback)(void *cbdata), void *aCallbackArgs)
{
    next();
    aCallback(aCallbackArgs);
}