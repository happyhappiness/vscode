void
Fs::Ufs::RebuildState::undoAdd()
{
    StoreEntry *added = currentEntry();
    assert(added);
    currentEntry(NULL);

    // TODO: Why bother with these two if we are going to release?!
    added->expireNow();
    added->releaseRequest();

    if (added->swap_filen > -1) {
        SwapDir *someDir = INDEXSD(added->swap_dirn);
        assert(someDir);
        if (UFSSwapDir *ufsDir = dynamic_cast<UFSSwapDir*>(someDir))
            ufsDir->undoAddDiskRestore(added);
        // else the entry was loaded from and/or is currently in a non-UFS dir
        // Thus, there is no use in preserving its disk file (the only purpose
        // of undoAddDiskRestore!), even if we could. Instead, we release the
        // the entry and [eventually] unlink its disk file or free its slot.
    }

    added->release();
}