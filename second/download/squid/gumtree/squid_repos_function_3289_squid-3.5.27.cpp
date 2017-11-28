bool
MemStore::startCaching(StoreEntry &e)
{
    sfileno index = 0;
    Ipc::StoreMapAnchor *slot = map->openForWriting(reinterpret_cast<const cache_key *>(e.key), index);
    if (!slot) {
        debugs(20, 5, HERE << "No room in mem-cache map to index " << e);
        return false;
    }

    assert(e.mem_obj);
    e.mem_obj->memCache.index = index;
    e.mem_obj->memCache.io = MemObject::ioWriting;
    slot->set(e);
    map->startAppending(index);
    e.memOutDecision(true);
    return true;
}