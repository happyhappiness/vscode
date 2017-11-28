void
Fs::Ufs::UFSSwapDir::maintain()
{
    /* We can't delete objects while rebuilding swap */

    /* XXX FIXME each store should start maintaining as it comes online. */

    if (StoreController::store_dirs_rebuilding)
        return;

    StoreEntry *e = NULL;

    int removed = 0;

    RemovalPurgeWalker *walker;

    double f = (double) (currentSize() - minSize()) / (maxSize() - minSize());

    f = f < 0.0 ? 0.0 : f > 1.0 ? 1.0 : f;

    int max_scan = (int) (f * 400.0 + 100.0);

    int max_remove = (int) (f * 70.0 + 10.0);

    /*
     * This is kinda cheap, but so we need this priority hack?
     */

    debugs(47, 3, HERE << "f=" << f << ", max_scan=" << max_scan << ", max_remove=" << max_remove  );

    walker = repl->PurgeInit(repl, max_scan);

    while (1) {
        if (currentSize() < minSize())
            break;

        if (removed >= max_remove)
            break;

        e = walker->Next(walker);

        if (!e)
            break;      /* no more objects */

        ++removed;

        e->release();
    }

    walker->Done(walker);
    debugs(47, (removed ? 2 : 3), HERE << path <<
           " removed " << removed << "/" << max_remove << " f=" <<
           std::setprecision(4) << f << " max_scan=" << max_scan);
}