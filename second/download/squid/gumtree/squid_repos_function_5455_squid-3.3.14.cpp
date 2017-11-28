void
DiskThreadsIOStrategy::init(void)
{
    if (initialised)
        return;

    squidaio_ctrl_pool = memPoolCreate("aio_ctrl", sizeof(squidaio_ctrl_t));

    initialised = true;

    /*
     * We'd like to call squidaio_init() here, but the configuration
     * hasn't been parsed yet and we don't know how many cache_dirs
     * there are, which means we don't know how many threads to start.
     */

    registerWithCacheManager();
}