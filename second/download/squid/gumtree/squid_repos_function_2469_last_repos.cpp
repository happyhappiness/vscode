void
destroyStoreEntry(void *data)
{
    debugs(20, 3, HERE << "destroyStoreEntry: destroying " <<  data);
    StoreEntry *e = static_cast<StoreEntry *>(static_cast<hash_link *>(data));
    assert(e != NULL);

    if (e == NullStoreEntry::getInstance())
        return;

    // Store::Root() is FATALly missing during shutdown
    if (e->swap_filen >= 0 && !shutting_down)
        e->disk().disconnect(*e);

    e->destroyMemObject();

    e->hashDelete();

    assert(e->key == NULL);

    delete e;
}