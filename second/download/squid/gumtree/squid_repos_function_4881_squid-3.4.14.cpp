void
CossSwapDir::optionBlockSizeDump(StoreEntry * e) const
{
    storeAppendPrintf(e, " block-size=%d", 1 << blksz_bits);
}