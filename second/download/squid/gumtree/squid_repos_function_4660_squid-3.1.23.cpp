void
UFSSwapDir::openLog()
{
    char *logPath;
    logPath = logFile();
    swaplog_fd = file_open(logPath, O_WRONLY | O_CREAT | O_BINARY);

    if (swaplog_fd < 0) {
        debugs(50, 1, "" << logPath << ": " << xstrerror());
        fatal("commonUfsDirOpenSwapLog: Failed to open swap log.");
    }

    debugs(50, 3, "Cache Dir #" << index << " log opened on FD " << swaplog_fd);

    if (0 == NumberOfUFSDirs)
        assert(NULL == UFSDirToGlobalDirMapping);

    ++NumberOfUFSDirs;

    assert(NumberOfUFSDirs <= Config.cacheSwap.n_configured);
}