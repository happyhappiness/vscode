static int
storeCleanupDoubleCheck(StoreEntry * e)
{
    SwapDir *SD = dynamic_cast<SwapDir *>(INDEXSD(e->swap_dirn));
    return (SD->doubleCheck(*e));
}