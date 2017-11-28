void
UFSSwapDir::dump(StoreEntry & entry) const
{
    storeAppendPrintf(&entry, " %" PRIu64 " %d %d",
                      (max_size >> 10),
                      l1,
                      l2);
    dumpOptions(&entry);
}