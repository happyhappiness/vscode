void
TransientsRr::create()
{
    if (!Config.onoff.collapsed_forwarding)
        return;

    const int64_t entryLimit = Transients::EntryLimit();
    if (entryLimit <= 0)
        return; // no SMP configured or a misconfiguration

    Must(!mapOwner);
    mapOwner = TransientsMap::Init(MapLabel, entryLimit);
    Must(!extrasOwner);
    extrasOwner = shm_new(TransientsMapExtras)(ExtrasLabel, entryLimit);
}