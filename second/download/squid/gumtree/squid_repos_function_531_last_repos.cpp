StoreEntry *
Transients::copyFromShm(const sfileno index)
{
    const TransientsMapExtras::Item &extra = extras->items[index];

    // create a brand new store entry and initialize it with stored info
    StoreEntry *e = storeCreatePureEntry(extra.url, extra.url,
                                         extra.reqFlags, extra.reqMethod);

    assert(e->mem_obj);
    e->mem_obj->method = extra.reqMethod;
    e->mem_obj->xitTable.io = MemObject::ioReading;
    e->mem_obj->xitTable.index = index;

    // TODO: Support collapsed revalidation for SMP-aware caches.
    e->setPublicKey(ksDefault);
    assert(e->key);

    // How do we know its SMP- and not just locally-collapsed? A worker gets
    // locally-collapsed entries from the local store_table, not Transients.
    // TODO: Can we remove smpCollapsed by not syncing non-transient entries?
    e->mem_obj->smpCollapsed = true;

    assert(!locals->at(index));
    // We do not lock e because we do not want to prevent its destruction;
    // e is tied to us via mem_obj so we will know when it is destructed.
    locals->at(index) = e;
    return e;
}