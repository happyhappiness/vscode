void
Transients::init()
{
    const int64_t entryLimit = EntryLimit();
    if (entryLimit <= 0)
        return; // no SMP support or a misconfiguration

    Must(!map);
    map = new TransientsMap(MapLabel);
    map->cleaner = this;

    extras = shm_old(TransientsMapExtras)(ExtrasLabel);

    locals = new Locals(entryLimit, 0);
}