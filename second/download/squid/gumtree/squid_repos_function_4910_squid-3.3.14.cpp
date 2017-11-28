int
Fs::Ufs::RebuildState::getNextFile(sfileno * filn_p, int *size)
{
    int fd = -1;
    int dirs_opened = 0;
    debugs(47, 3, HERE << "flag=" << flags.init  << ", " <<
           sd->index  << ": /"<< std::setfill('0') << std::hex <<
           std::uppercase << std::setw(2) << curlvl1  << "/" << std::setw(2) <<
           curlvl2);

    if (done)
        return -2;

    while (fd < 0 && done == 0) {
        fd = -1;

        if (0 == flags.init) {  /* initialize, open first file */
            done = 0;
            curlvl1 = 0;
            curlvl2 = 0;
            in_dir = 0;
            flags.init = 1;
            assert(Config.cacheSwap.n_configured > 0);
        }

        if (0 == in_dir) {  /* we need to read in a new directory */
            snprintf(fullpath, MAXPATHLEN, "%s/%02X/%02X",
                     sd->path,
                     curlvl1, curlvl2);

            if (dirs_opened)
                return -1;

            td = opendir(fullpath);

            ++dirs_opened;

            if (td == NULL) {
                debugs(47, DBG_IMPORTANT, HERE << "error in opendir (" << fullpath << "): " << xstrerror());
            } else {
                entry = readdir(td);    /* skip . and .. */
                entry = readdir(td);

                if (entry == NULL && errno == ENOENT)
                    debugs(47, DBG_IMPORTANT, HERE << "WARNING: directory does not exist!");
                debugs(47, 3, HERE << "Directory " << fullpath);
            }
        }

        if (td != NULL && (entry = readdir(td)) != NULL) {
            ++in_dir;

            if (sscanf(entry->d_name, "%x", &fn) != 1) {
                debugs(47, 3, HERE << "invalid entry " << entry->d_name);
                continue;
            }

            if (!UFSSwapDir::FilenoBelongsHere(fn, sd->index, curlvl1, curlvl2)) {
                debugs(47, 3, HERE << std::setfill('0') <<
                       std::hex << std::uppercase << std::setw(8) << fn  <<
                       " does not belong in " << std::dec << sd->index  << "/" <<
                       curlvl1  << "/" << curlvl2);

                continue;
            }

            if (sd->mapBitTest(fn)) {
                debugs(47, 3, HERE << "Locked, continuing with next.");
                continue;
            }

            snprintf(fullfilename, MAXPATHLEN, "%s/%s",
                     fullpath, entry->d_name);
            debugs(47, 3, HERE << "Opening " << fullfilename);
            fd = file_open(fullfilename, O_RDONLY | O_BINARY);

            if (fd < 0)
                debugs(47, DBG_IMPORTANT, HERE << "error opening " << fullfilename << ": " << xstrerror());
            else
                ++store_open_disk_fd;

            continue;
        }

        if (td != NULL)
            closedir(td);

        td = NULL;

        in_dir = 0;

        if (sd->validL2(++curlvl2))
            continue;

        curlvl2 = 0;

        if (sd->validL1(++curlvl1))
            continue;

        curlvl1 = 0;

        done = 1;
    }

    *filn_p = fn;
    return fd;
}