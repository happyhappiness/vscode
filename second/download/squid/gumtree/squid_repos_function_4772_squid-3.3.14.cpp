void
CossSwapDir::optionIODump(StoreEntry * e) const
{
    storeAppendPrintf(e, " IOEngine=%s", ioModule);
}