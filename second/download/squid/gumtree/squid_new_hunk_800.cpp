Rock::SwapDir::dumpRateOption(StoreEntry * e) const
{
    if (fileConfig.ioRate >= 0)
        storeAppendPrintf(e, " max-swap-rate=%d", fileConfig.ioRate);
}

/// parses size-specific options; mimics ::SwapDir::optionObjectSizeParse()
bool
Rock::SwapDir::parseSizeOption(char const *option, const char *value, int reconfig)
{
    uint64_t *storedSize;
    if (strcmp(option, "slot-size") == 0)
        storedSize = &slotSize;
    else
        return false;

    if (!value)
        self_destruct();

    // TODO: handle size units and detect parsing errors better
    const uint64_t newSize = strtoll(value, NULL, 10);
    if (newSize <= 0) {
        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must be positive; got: " << newSize);
        self_destruct();
    }

    if (newSize <= sizeof(DbCellHeader)) {
        debugs(3, DBG_CRITICAL, "FATAL: cache_dir " << path << ' ' << option << " must exceed " << sizeof(DbCellHeader) << "; got: " << newSize);
        self_destruct();
    }

    if (!reconfig)
        *storedSize = newSize;
    else if (*storedSize != newSize) {
        debugs(3, DBG_IMPORTANT, "WARNING: cache_dir " << path << ' ' << option
               << " cannot be changed dynamically, value left unchanged: " <<
               *storedSize);
    }

    return true;
}

/// reports size-specific options; mimics ::SwapDir::optionObjectSizeDump()
void
Rock::SwapDir::dumpSizeOption(StoreEntry * e) const
{
    storeAppendPrintf(e, " slot-size=%" PRId64, slotSize);
}

/// check the results of the configuration; only level-0 debugging works here
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

void
Rock::SwapDir::rebuild()
{
    //++StoreController::store_dirs_rebuilding; // see Rock::SwapDir::init()
    AsyncJob::Start(new Rebuild(this));
}

bool
Rock::SwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    if (!::SwapDir::canStore(e, sizeof(DbCellHeader)+diskSpaceNeeded, load))
        return false;

