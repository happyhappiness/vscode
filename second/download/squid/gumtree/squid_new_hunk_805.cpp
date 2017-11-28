    return lpath;
}

void
Fs::Ufs::UFSSwapDir::openLog()
{
    assert(NumberOfUFSDirs || !UFSDirToGlobalDirMapping);
    ++NumberOfUFSDirs;
    assert(NumberOfUFSDirs <= Config.cacheSwap.n_configured);

    if (rebuilding_) { // we did not close the temporary log used for rebuilding
        assert(swaplog_fd >= 0);
        return;
    }

    char *logPath;
    logPath = logFile();
    swaplog_fd = file_open(logPath, O_WRONLY | O_CREAT | O_BINARY);

    if (swaplog_fd < 0) {
        debugs(50, DBG_IMPORTANT, "ERROR opening swap log " << logPath << ": " << xstrerror());
        fatal("UFSSwapDir::openLog: Failed to open swap log.");
    }

    debugs(50, 3, HERE << "Cache Dir #" << index << " log opened on FD " << swaplog_fd);
}

void
Fs::Ufs::UFSSwapDir::closeLog()
{
    if (swaplog_fd < 0) /* not open */
        return;

    --NumberOfUFSDirs;
    assert(NumberOfUFSDirs >= 0);
    if (!NumberOfUFSDirs)
        safe_free(UFSDirToGlobalDirMapping);

    if (rebuilding_) // we cannot close the temporary log used for rebuilding
        return;

    file_close(swaplog_fd);

    debugs(47, 3, "Cache Dir #" << index << " log closed on FD " << swaplog_fd);

    swaplog_fd = -1;
}

bool
Fs::Ufs::UFSSwapDir::validL1(int anInt) const
{
    return anInt < l1;
