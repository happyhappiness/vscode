void
Rock::SwapDir::dumpSizeOption(StoreEntry * e) const
{
    storeAppendPrintf(e, " slot-size=%" PRId64, slotSize);
}