void
DiskThreadsIOStrategy::done(void)
{
    if (!initialised)
        return;

    squidaio_shutdown();

    delete squidaio_ctrl_pool;

    squidaio_ctrl_pool = NULL;

    initialised = false;
}