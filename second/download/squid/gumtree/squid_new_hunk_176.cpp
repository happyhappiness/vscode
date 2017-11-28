/* ========== LOCAL FUNCTIONS ABOVE, GLOBAL FUNCTIONS BELOW ========== */

void
CossSwapDir::statfs(StoreEntry & sentry) const
{
    storeAppendPrintf(&sentry, "\n");
    storeAppendPrintf(&sentry, "Maximum Size: %" PRIu64 " KB\n", maxSize() >> 10);
    storeAppendPrintf(&sentry, "Current Size: %.2f KB\n", currentSize() / 1024.0);
    storeAppendPrintf(&sentry, "Percent Used: %0.2f%%\n",
                      Math::doublePercent(currentSize(), maxSize()) );
    storeAppendPrintf(&sentry, "Number of object collisions: %d\n", (int) numcollisions);
#if 0
    /* is this applicable? I Hope not .. */
    storeAppendPrintf(sentry, "Filemap bits in use: %d of %d (%d%%)\n",
                      SD->map->numFilesInMap(), SD->map->capacity(),
                      Math::intPercent(SD->map->numFilesInMap(), SD->map->capacity()));
#endif

    //    storeAppendPrintf(&sentry, "Pending operations: %d out of %d\n", io->aq.aq_numpending, MAX_ASYNCOP);
    storeAppendPrintf(&sentry, "Flags:");

    if (flags.selected)
