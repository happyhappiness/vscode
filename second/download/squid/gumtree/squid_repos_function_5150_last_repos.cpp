void
Fs::Ufs::UFSSwapDir::dump(StoreEntry & entry) const
{
    storeAppendPrintf(&entry, " %" PRIu64 " %d %d", maxSize() >> 20, l1, l2);
    dumpOptions(&entry);
}