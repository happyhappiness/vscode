storeAppendPrintf(&sentry, "Filemap bits in use: %d of %d (%d%%)\n",
                      map->n_files_in_map, map->max_n_files,
                      Math::intPercent(map->n_files_in_map, map->max_n_files));