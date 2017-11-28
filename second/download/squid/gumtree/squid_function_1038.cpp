void
Rock::SwapDir::validateOptions()
{
    if (slotSize <= 0)
        fatal("Rock store requires a positive slot-size");

    const int64_t maxSizeRoundingWaste = 1024 * 1024; // size is configured in MB
    const int64_t slotSizeRoundingWaste = slotSize;
    const int64_t maxRoundingWaste =
        max(maxSizeRoundingWaste, slotSizeRoundingWaste);

    // an entry consumes at least one slot; round up to reduce false warnings
    const int64_t blockSize = static_cast<int64_t>(slotSize);
    const int64_t maxObjSize = max(blockSize,
                                   ((maxObjectSize()+blockSize-1)/blockSize)*blockSize);

    // Does the "sfileno*max-size" limit match configured db capacity?
    const double entriesMayOccupy = entryLimitAbsolute()*static_cast<double>(maxObjSize);
    if (entriesMayOccupy + maxRoundingWaste < maxSize()) {
        const int64_t diskWasteSize = maxSize() - static_cast<int64_t>(entriesMayOccupy);
        debugs(47, DBG_CRITICAL, "WARNING: Rock cache_dir " << path << " wastes disk space due to entry limits:" <<
               "\n\tconfigured db capacity: " << maxSize() << " bytes" <<
               "\n\tconfigured db slot size: " << slotSize << " bytes" <<
               "\n\tconfigured maximum entry size: " << maxObjectSize() << " bytes" <<
               "\n\tmaximum number of cache_dir entries supported by Squid: " << entryLimitAbsolute() <<
               "\n\tdisk space all entries may use: " << entriesMayOccupy << " bytes" <<
               "\n\tdisk space wasted: " << diskWasteSize << " bytes");
    }

    // Does the "absolute slot count" limit match configured db capacity?
    const double slotsMayOccupy = slotLimitAbsolute()*static_cast<double>(slotSize);
    if (slotsMayOccupy + maxRoundingWaste < maxSize()) {
        const int64_t diskWasteSize = maxSize() - static_cast<int64_t>(entriesMayOccupy);
        debugs(47, DBG_CRITICAL, "WARNING: Rock cache_dir " << path << " wastes disk space due to slot limits:" <<
               "\n\tconfigured db capacity: " << maxSize() << " bytes" <<
               "\n\tconfigured db slot size: " << slotSize << " bytes" <<
               "\n\tmaximum number of rock cache_dir slots supported by Squid: " << slotLimitAbsolute() <<
               "\n\tdisk space all slots may use: " << slotsMayOccupy << " bytes" <<
               "\n\tdisk space wasted: " << diskWasteSize << " bytes");
    }
}