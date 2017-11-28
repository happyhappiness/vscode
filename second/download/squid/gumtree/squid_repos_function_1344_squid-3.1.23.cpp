void
LeakFinder::dump()
{
    if (0 == count)
        return;

    if (squid_curtime == last_dump)
        return;

    last_dump = squid_curtime;

    debugs(45, 1, "Tracking " << count << " pointers");

    hash_first(table);

    LeakFinderPtr *c;

    while ((c = (LeakFinderPtr *)hash_next(table))) {
        debugs(45, 1, std::setw(20) << c->key << " last used " << std::setw(9) << (squid_curtime - c->when) <<
               " seconds ago by " << c->file << ":" << c->line);
    }
}