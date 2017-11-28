static void
update_maxobjsize(void)
{
    int i;
    int64_t ms = -1;

    for (i = 0; i < Config.cacheSwap.n_configured; i++) {
        assert (Config.cacheSwap.swapDirs[i].getRaw());

        if (dynamic_cast<SwapDir *>(Config.cacheSwap.swapDirs[i].getRaw())->
                max_objsize > ms)
            ms = dynamic_cast<SwapDir *>(Config.cacheSwap.swapDirs[i].getRaw())->max_objsize;
    }
    store_maxobjsize = ms;
}