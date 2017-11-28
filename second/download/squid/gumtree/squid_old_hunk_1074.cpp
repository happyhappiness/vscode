    storeAppendPrintf(&sentry, "Current Size: %.2f KB\n", currentSize() / 1024.0);
    storeAppendPrintf(&sentry, "Percent Used: %0.2f%%\n",
                      Math::doublePercent(currentSize(), maxSize()));
    storeAppendPrintf(&sentry, "Filemap bits in use: %d of %d (%d%%)\n",
                      map->numFilesInMap(), map->capacity(),
                      Math::intPercent(map->numFilesInMap(), map->capacity()));
    x = storeDirGetUFSStats(path, &totl_kb, &free_kb, &totl_in, &free_in);

    if (0 == x) {
        storeAppendPrintf(&sentry, "Filesystem Space in use: %d/%d KB (%d%%)\n",
                          totl_kb - free_kb,
                          totl_kb,
                          Math::intPercent(totl_kb - free_kb, totl_kb));
