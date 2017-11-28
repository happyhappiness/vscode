void
CossSwapDir::dump(StoreEntry &entry)const
{
    storeAppendPrintf(&entry, " %" PRIu64, maxSize() >> 20);
    dumpOptions(&entry);
}