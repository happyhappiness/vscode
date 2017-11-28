    storeAppendPrintf(&e, "\n");
    storeAppendPrintf(&e, "Maximum Size: %" PRIu64 " KB\n", maxSize() >> 10);
    storeAppendPrintf(&e, "Current Size: %.2f KB %.2f%%\n",
                      currentSize() / 1024.0,
                      Math::doublePercent(currentSize(), maxSize()));

    const int entryLimit = entryLimitActual();
    const int slotLimit = slotLimitActual();
    storeAppendPrintf(&e, "Maximum entries: %9d\n", entryLimit);
    if (map && entryLimit > 0) {
        const int entryCount = map->entryCount();
        storeAppendPrintf(&e, "Current entries: %9d %.2f%%\n",
                          entryCount, (100.0 * entryCount / entryLimit));
    }

    storeAppendPrintf(&e, "Maximum slots:   %9d\n", slotLimit);
    if (map && slotLimit > 0) {
        const unsigned int slotsFree = !freeSlots ? 0 : freeSlots->size();
        if (slotsFree <= static_cast<const unsigned int>(slotLimit)) {
            const int usedSlots = slotLimit - static_cast<const int>(slotsFree);
            storeAppendPrintf(&e, "Used slots:      %9d %.2f%%\n",
                              usedSlots, (100.0 * usedSlots / slotLimit));
        }
        if (slotLimit < 100) { // XXX: otherwise too expensive to count
            Ipc::ReadWriteLockStats stats;
            map->updateStats(stats);
            stats.dump(e);
        }
    }

    storeAppendPrintf(&e, "Pending operations: %d out of %d\n",
                      store_open_disk_fd, Config.max_open_disk_fds);

