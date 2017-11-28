void
Transients::startWriting(StoreEntry *e, const RequestFlags &reqFlags,
                         const HttpRequestMethod &reqMethod)
{
    assert(e);
    assert(e->mem_obj);
    assert(e->mem_obj->xitTable.index < 0);

    if (!map) {
        debugs(20, 5, "No map to add " << *e);
        return;
    }

    sfileno index = 0;
    Ipc::StoreMapAnchor *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e->key), index);
    if (!slot) {
        debugs(20, 5, "collision registering " << *e);
        return;
    }

    try {
        if (copyToShm(*e, index, reqFlags, reqMethod)) {
            slot->set(*e);
            e->mem_obj->xitTable.io = MemObject::ioWriting;
            e->mem_obj->xitTable.index = index;
            map->startAppending(index);
            // keep write lock -- we will be supplying others with updates
            return;
        }
        // fall through to the error handling code
    } catch (const std::exception &x) { // TODO: should we catch ... as well?
        debugs(20, 2, "error keeping entry " << index <<
               ' ' << *e << ": " << x.what());
        // fall through to the error handling code
    }

    map->abortWriting(index);
}