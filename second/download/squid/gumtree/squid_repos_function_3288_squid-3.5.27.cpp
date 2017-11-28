bool
MemStore::shouldCache(StoreEntry &e) const
{
    if (e.mem_status == IN_MEMORY) {
        debugs(20, 5, "already loaded from mem-cache: " << e);
        return false;
    }

    if (e.mem_obj && e.mem_obj->memCache.offset > 0) {
        debugs(20, 5, "already written to mem-cache: " << e);
        return false;
    }

    if (!e.memoryCachable()) {
        debugs(20, 7, HERE << "Not memory cachable: " << e);
        return false; // will not cache due to entry state or properties
    }

    assert(e.mem_obj);

    if (!e.mem_obj->vary_headers.isEmpty()) {
        // XXX: We must store/load SerialisedMetaData to cache Vary in RAM
        debugs(20, 5, "Vary not yet supported: " << e.mem_obj->vary_headers);
        return false;
    }

    const int64_t expectedSize = e.mem_obj->expectedReplySize(); // may be < 0

    // objects of unknown size are not allowed into memory cache, for now
    if (expectedSize < 0) {
        debugs(20, 5, "Unknown expected size: " << e);
        return false;
    }

    const int64_t loadedSize = e.mem_obj->endOffset();
    const int64_t ramSize = max(loadedSize, expectedSize);

    if (ramSize > maxObjectSize()) {
        debugs(20, 5, HERE << "Too big max(" <<
               loadedSize << ", " << expectedSize << "): " << e);
        return false; // will not cache due to cachable entry size limits
    }

    if (!e.mem_obj->isContiguous()) {
        debugs(20, 5, "not contiguous");
        return false;
    }

    if (!map) {
        debugs(20, 5, HERE << "No map to mem-cache " << e);
        return false;
    }

    if (EBIT_TEST(e.flags, ENTRY_SPECIAL)) {
        debugs(20, 5, "Not mem-caching ENTRY_SPECIAL " << e);
        return false;
    }

    return true;
}