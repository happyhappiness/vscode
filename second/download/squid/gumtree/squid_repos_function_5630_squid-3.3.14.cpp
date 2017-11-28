void
DiskdIOStrategy::optionQ1Dump(StoreEntry * e) const
{
    storeAppendPrintf(e, " Q1=%d", magic1);
}