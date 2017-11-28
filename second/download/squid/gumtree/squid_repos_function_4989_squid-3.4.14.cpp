void
Fs::Ufs::RebuildState::rebuildFromSwapLog()
{
    StoreSwapLogData swapData;

    if (LogParser->ReadRecord(swapData) != 1) {
        debugs(47, DBG_IMPORTANT, "Done reading " << sd->path << " swaplog (" << n_read << " entries)");
        LogParser->Close();
        delete LogParser;
        LogParser = NULL;
        _done = true;
        return;
    }

    ++n_read;

    if (!swapData.sane()) {
        ++counts.invalid;
        return;
    }

    /*
     * BC: during 2.4 development, we changed the way swap file
     * numbers are assigned and stored.  The high 16 bits used
     * to encode the SD index number.  There used to be a call
     * to storeDirProperFileno here that re-assigned the index
     * bits.  Now, for backwards compatibility, we just need
     * to mask it off.
     */
    swapData.swap_filen &= 0x00FFFFFF;

    debugs(47, 3, HERE << swap_log_op_str[(int) swapData.op]  << " " <<
           storeKeyText(swapData.key)  << " "<< std::setfill('0') <<
           std::hex << std::uppercase << std::setw(8) <<
           swapData.swap_filen);

    if (swapData.op == SWAP_LOG_ADD) {
        (void) 0;
    } else if (swapData.op == SWAP_LOG_DEL) {
        /* Delete unless we already have a newer copy anywhere in any store */
        /* this needs to become
         * 1) unpack url
         * 2) make synthetic request with headers ?? or otherwise search
         * for a matching object in the store
         * TODO FIXME change to new async api
         */
        currentEntry (Store::Root().get(swapData.key));

        if (currentEntry() != NULL && swapData.lastref >= e->lastref) {
            undoAdd();
            --counts.objcount;
            ++counts.cancelcount;
        }
        return;
    } else {
        const double
        x = ::log(static_cast<double>(++counts.bad_log_op)) / ::log(10.0);

        if (0.0 == x - (double) (int) x)
            debugs(47, DBG_IMPORTANT, "WARNING: " << counts.bad_log_op << " invalid swap log entries found");

        ++counts.invalid;

        return;
    }

    ++counts.scancount; // XXX: should not this be incremented earlier?

    if (!sd->validFileno(swapData.swap_filen, 0)) {
        ++counts.invalid;
        return;
    }

    if (EBIT_TEST(swapData.flags, KEY_PRIVATE)) {
        ++counts.badflags;
        return;
    }

    /* this needs to become
     * 1) unpack url
     * 2) make synthetic request with headers ?? or otherwise search
     * for a matching object in the store
     * TODO FIXME change to new async api
     */
    currentEntry (Store::Root().get(swapData.key));

    int used;           /* is swapfile already in use? */

    used = sd->mapBitTest(swapData.swap_filen);

    /* If this URL already exists in the cache, does the swap log
     * appear to have a newer entry?  Compare 'lastref' from the
     * swap log to e->lastref. */
    /* is the log entry newer than current entry? */
    int disk_entry_newer = currentEntry() ? (swapData.lastref > currentEntry()->lastref ? 1 : 0) : 0;

    if (used && !disk_entry_newer) {
        /* log entry is old, ignore it */
        ++counts.clashcount;
        return;
    } else if (used && currentEntry() && currentEntry()->swap_filen == swapData.swap_filen && currentEntry()->swap_dirn == sd->index) {
        /* swapfile taken, same URL, newer, update meta */

        if (currentEntry()->store_status == STORE_OK) {
            currentEntry()->lastref = swapData.timestamp;
            currentEntry()->timestamp = swapData.timestamp;
            currentEntry()->expires = swapData.expires;
            currentEntry()->lastmod = swapData.lastmod;
            currentEntry()->flags = swapData.flags;
            currentEntry()->refcount += swapData.refcount;
            sd->dereference(*currentEntry(), false);
        } else {
            debug_trap("commonUfsDirRebuildFromSwapLog: bad condition");
            debugs(47, DBG_IMPORTANT, HERE << "bad condition");
        }
        return;
    } else if (used) {
        /* swapfile in use, not by this URL, log entry is newer */
        /* This is sorta bad: the log entry should NOT be newer at this
         * point.  If the log is dirty, the filesize check should have
         * caught this.  If the log is clean, there should never be a
         * newer entry. */
        debugs(47, DBG_IMPORTANT, "WARNING: newer swaplog entry for dirno " <<
               sd->index  << ", fileno "<< std::setfill('0') << std::hex <<
               std::uppercase << std::setw(8) << swapData.swap_filen);

        /* I'm tempted to remove the swapfile here just to be safe,
         * but there is a bad race condition in the NOVM version if
         * the swapfile has recently been opened for writing, but
         * not yet opened for reading.  Because we can't map
         * swapfiles back to StoreEntrys, we don't know the state
         * of the entry using that file.  */
        /* We'll assume the existing entry is valid, probably because
         * were in a slow rebuild and the the swap file number got taken
         * and the validation procedure hasn't run. */
        assert(flags.need_to_validate);
        ++counts.clashcount;
        return;
    } else if (currentEntry() && !disk_entry_newer) {
        /* key already exists, current entry is newer */
        /* keep old, ignore new */
        ++counts.dupcount;
        return;
    } else if (currentEntry()) {
        /* key already exists, this swapfile not being used */
        /* junk old, load new */
        undoAdd();
        --counts.objcount;
        ++counts.dupcount;
    } else {
        /* URL doesnt exist, swapfile not in use */
        /* load new */
        (void) 0;
    }

    ++counts.objcount;

    currentEntry(sd->addDiskRestore(swapData.key,
                                    swapData.swap_filen,
                                    swapData.swap_file_sz,
                                    swapData.expires,
                                    swapData.timestamp,
                                    swapData.lastref,
                                    swapData.lastmod,
                                    swapData.refcount,
                                    swapData.flags,
                                    (int) flags.clean));

    storeDirSwapLog(currentEntry(), SWAP_LOG_ADD);
}