storeAppendPrintf(&sentry, "Filemap bits in use: %d of %d (%d%%)\n",
                      map->numFilesInMap(), map->capacity(),
                      Math::intPercent(map->numFilesInMap(), map->capacity()));