Rock::SwapDir::dumpRateOption(StoreEntry * e) const
{
    if (fileConfig.ioRate >= 0)
        storeAppendPrintf(e, " max-swap-rate=%d", fileConfig.ioRate);
}

/// check the results of the configuration; only level-0 debugging works here
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

void
Rock::SwapDir::rebuild()
{
    //++StoreController::store_dirs_rebuilding; // see Rock::SwapDir::init()
    AsyncJob::Start(new Rebuild(this));
}

/* Add a new object to the cache with empty memory copy and pointer to disk
 * use to rebuild store from disk. Based on UFSSwapDir::addDiskRestore */
bool
Rock::SwapDir::addEntry(const int filen, const DbCellHeader &header, const StoreEntry &from)
{
    debugs(47, 8, HERE << &from << ' ' << from.getMD5Text() <<
           ", filen="<< std::setfill('0') << std::hex << std::uppercase <<
           std::setw(8) << filen);

    sfileno newLocation = 0;
    if (Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(from.key), newLocation)) {
        if (filen == newLocation) {
            slot->set(from);
            map->extras(filen) = header;
        } // else some other, newer entry got into our cell
        map->closeForWriting(newLocation, false);
        return filen == newLocation;
    }

    return false;
}

bool
Rock::SwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    if (!::SwapDir::canStore(e, sizeof(DbCellHeader)+diskSpaceNeeded, load))
        return false;

