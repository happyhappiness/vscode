void
Rock::SwapDir::maintain()
{
    debugs(47,3, HERE << "cache_dir[" << index << "] guards: " <<
           !repl << !map << !full() << StoreController::store_dirs_rebuilding);

    if (!repl)
        return; // no means (cannot find a victim)

    if (!map)
        return; // no victims (yet)

    if (!full())
        return; // no need (to find a victim)

    // XXX: UFSSwapDir::maintain says we must quit during rebuild
    if (StoreController::store_dirs_rebuilding)
        return;

    debugs(47,3, HERE << "cache_dir[" << index << "] state: " << map->full() <<
           ' ' << currentSize() << " < " << diskOffsetLimit());

    // Hopefully, we find a removable entry much sooner (TODO: use time?)
    const int maxProbed = 10000;
    RemovalPurgeWalker *walker = repl->PurgeInit(repl, maxProbed);

    // It really should not take that long, but this will stop "infinite" loops
    const int maxFreed = 1000;
    int freed = 0;
    // TODO: should we purge more than needed to minimize overheads?
    for (; freed < maxFreed && full(); ++freed) {
        if (StoreEntry *e = walker->Next(walker))
            e->release(); // will call our unlink() method
        else
            break; // no more objects
    }

    debugs(47,2, HERE << "Rock cache_dir[" << index << "] freed " << freed <<
           " scanned " << walker->scanned << '/' << walker->locked);

    walker->Done(walker);

    if (full()) {
        debugs(47, DBG_CRITICAL, "ERROR: Rock cache_dir[" << index << "] " <<
               "is still full after freeing " << freed << " entries. A bug?");
    }
}