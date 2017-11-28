void
Rock::SwapDir::validateOptions()
{
    if (max_objsize <= 0)
        fatal("Rock store requires a positive max-size");

    const int64_t maxSizeRoundingWaste = 1024 * 1024; // size is configured in MB
    const int64_t maxObjectSizeRoundingWaste = maxObjectSize();
    const int64_t maxRoundingWaste =
        max(maxSizeRoundingWaste, maxObjectSizeRoundingWaste);
    const int64_t usableDiskSize = diskOffset(entryLimitAllowed());
    const int64_t diskWasteSize = maxSize() - usableDiskSize;
    Must(diskWasteSize >= 0);

    // warn if maximum db size is not reachable due to sfileno limit
    if (entryLimitAllowed() == entryLimitHigh() &&
            diskWasteSize >= maxRoundingWaste) {
        debugs(47, DBG_CRITICAL, "Rock store cache_dir[" << index << "] '" << path << "':");
        debugs(47, DBG_CRITICAL, "\tmaximum number of entries: " << entryLimitAllowed());
        debugs(47, DBG_CRITICAL, "\tmaximum object size: " << maxObjectSize() << " Bytes");
        debugs(47, DBG_CRITICAL, "\tmaximum db size: " << maxSize() << " Bytes");
        debugs(47, DBG_CRITICAL, "\tusable db size:  " << usableDiskSize << " Bytes");
        debugs(47, DBG_CRITICAL, "\tdisk space waste: " << diskWasteSize << " Bytes");
        debugs(47, DBG_CRITICAL, "WARNING: Rock store config wastes space.");
    }
}