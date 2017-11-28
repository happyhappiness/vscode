void
StoreController::stat(StoreEntry &output) const
{
    storeAppendPrintf(&output, "Store Directory Statistics:\n");
    storeAppendPrintf(&output, "Store Entries          : %lu\n",
                      (unsigned long int)StoreEntry::inUseCount());
    storeAppendPrintf(&output, "Maximum Swap Size      : %" PRIu64 " KB\n",
                      maxSize() >> 10);
    storeAppendPrintf(&output, "Current Store Swap Size: %.2f KB\n",
                      currentSize() / 1024.0);
    storeAppendPrintf(&output, "Current Capacity       : %.2f%% used, %.2f%% free\n",
                      Math::doublePercent(currentSize(), maxSize()),
                      Math::doublePercent((maxSize() - currentSize()), maxSize()));

    if (memStore)
        memStore->stat(output);

    /* now the swapDir */
    swapDir->stat(output);
}