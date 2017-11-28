void
CossSwapDir::dump(StoreEntry &entry)const
{
    storeAppendPrintf(&entry, " %" PRIu64, (max_size >> 10));
    dumpOptions(&entry);
}