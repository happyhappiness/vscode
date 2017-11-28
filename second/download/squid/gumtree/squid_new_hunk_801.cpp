
    if (theFile->error())
        fatalf("Rock cache_dir at %s failed to open db file: %s", filePath,
               xstrerror());

    debugs(47, 2, "Rock cache_dir[" << index << "] limits: " <<
           std::setw(12) << maxSize() << " disk bytes, " <<
           std::setw(7) << map->entryLimit() << " entries, and " <<
           std::setw(7) << map->sliceLimit() << " slots");

    rebuild();
}

void
Rock::SwapDir::closeCompleted()
