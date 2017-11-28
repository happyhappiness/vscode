void
SBuf::clear()
{
#if 0
    //enabling this code path, the store will be freed and reinitialized
    store_ = GetStorePrototype(); //uncomment to actually free storage upon clear()
#else
    //enabling this code path, we try to release the store without deallocating it.
    // will be lazily reallocated if needed.
    if (store_->LockCount() == 1)
        store_->clear();
#endif
    len_ = 0;
    off_ = 0;
    ++stats.clear;
}