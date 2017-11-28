bool
unlinkdNeeded(void)
{
    // we should start unlinkd if there are any cache_dirs using it
    for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
        const RefCount<SwapDir> sd = Config.cacheSwap.swapDirs[i];
        if (sd->unlinkdUseful())
            return true;
    }

    return false;
}