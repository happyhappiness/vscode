void
storeDirCloseSwapLogs()
{
    for (int dirn = 0; dirn < Config.cacheSwap.n_configured; ++dirn)
        INDEXSD(dirn)->closeLog();
}