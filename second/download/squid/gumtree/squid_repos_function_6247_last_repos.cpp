void
DiskThreadsIOStrategy::init(void)
{
    if (initialised)
        return;

    initialised = true;

    /*
     * We'd like to call squidaio_init() here, but the configuration
     * hasn't been parsed yet and we don't know how many cache_dirs
     * there are, which means we don't know how many threads to start.
     */

    registerWithCacheManager();
}