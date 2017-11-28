void
MemStore::considerKeeping(StoreEntry &e)
{
    if (!keepInLocalMemory(e))
        return;

    // since we copy everything at once, we can only keep complete entries
    if (e.store_status != STORE_OK) {
        debugs(20, 7, HERE << "Incomplete: " << e);
        return;
    }

    assert(e.mem_obj);

    const int64_t loadedSize = e.mem_obj->endOffset();
    const int64_t expectedSize = e.mem_obj->expectedReplySize();

    // objects of unknown size are not allowed into memory cache, for now
    if (expectedSize < 0) {
        debugs(20, 5, HERE << "Unknown expected size: " << e);
        return;
    }

    // since we copy everything at once, we can only keep fully loaded entries
    if (loadedSize != expectedSize) {
        debugs(20, 7, HERE << "partially loaded: " << loadedSize << " != " <<
               expectedSize);
        return;
    }

    if (e.mem_obj->vary_headers) {
        // XXX: We must store/load SerialisedMetaData to cache Vary in RAM
        debugs(20, 5, "Vary not yet supported: " << e.mem_obj->vary_headers);
        return;
    }

    keep(e); // may still fail
}