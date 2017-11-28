int
DiskThreadsIOStrategy::load()
{
    int loadav;
    int ql;

    ql = aioQueueSize();

    if (ql == 0)
        loadav = 0;

    loadav = ql * 1000 / MAGIC1;

    debugs(47, 9, "DiskThreadsIOStrategy::load: load=" << loadav);

    return loadav;
}