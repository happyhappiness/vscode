bool
MemStore::keepInLocalMemory(const StoreEntry &e) const
{
    if (!e.memoryCachable()) {
        debugs(20, 7, HERE << "Not memory cachable: " << e);
        return false; // will not cache due to entry state or properties
    }

    assert(e.mem_obj);
    const int64_t loadedSize = e.mem_obj->endOffset();
    const int64_t expectedSize = e.mem_obj->expectedReplySize(); // may be < 0
    const int64_t ramSize = max(loadedSize, expectedSize);

    if (ramSize > static_cast<int64_t>(Config.Store.maxInMemObjSize)) {
        debugs(20, 5, HERE << "Too big max(" <<
               loadedSize << ", " << expectedSize << "): " << e);
        return false; // will not cache due to cachable entry size limits
    }

    if (!willFit(ramSize)) {
        debugs(20, 5, HERE << "Wont fit max(" <<
               loadedSize << ", " << expectedSize << "): " << e);
        return false; // will not cache due to memory cache slot limit
    }

    return true;
}