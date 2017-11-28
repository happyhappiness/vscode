void
storeDirCloseSwapLogs(void)
{
    for (int dirn = 0; dirn < Config.cacheSwap.n_configured; ++dirn)
        dynamic_cast<SwapDir *>(INDEXSD(dirn))->closeLog();
}