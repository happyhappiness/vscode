int
NumberOfKids()
{
    // no kids in no-daemon mode
    if (!InDaemonMode())
        return 0;

    // XXX: detect and abort when called before workers/cache_dirs are parsed

    const int rockDirs = Config.cacheSwap.n_strands;

    const bool needCoord = Config.workers > 1 || rockDirs > 0;
    return (needCoord ? 1 : 0) + Config.workers + rockDirs;
}