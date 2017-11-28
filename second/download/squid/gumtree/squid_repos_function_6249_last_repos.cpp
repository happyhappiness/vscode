void
DiskThreadsIOStrategy::done(void)
{
    if (!initialised)
        return;

    squidaio_shutdown();

    initialised = false;
}