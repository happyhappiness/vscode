void
Fs::Ufs::UFSSwapDir::optionIODump(StoreEntry * e) const
{
    storeAppendPrintf(e, " IOEngine=%s", ioType);
}