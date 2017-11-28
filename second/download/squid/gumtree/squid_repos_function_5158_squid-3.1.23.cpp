void
DiskdIOStrategy::optionQ2Dump(StoreEntry * e) const
{
    storeAppendPrintf(e, " Q2=%d", magic2);
}