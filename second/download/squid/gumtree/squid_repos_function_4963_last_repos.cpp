void
Rock::SwapDir::ioCompletedNotification()
{
    if (!theFile)
        fatalf("Rock cache_dir failed to initialize db file: %s", filePath);

    if (theFile->error()) {
        int xerrno = errno; // XXX: where does errno come from
        fatalf("Rock cache_dir at %s failed to open db file: %s", filePath,
               xstrerr(xerrno));
    }

    debugs(47, 2, "Rock cache_dir[" << index << "] limits: " <<
           std::setw(12) << maxSize() << " disk bytes, " <<
           std::setw(7) << map->entryLimit() << " entries, and " <<
           std::setw(7) << map->sliceLimit() << " slots");

    rebuild();
}