void
MemStore::completeWriting(StoreEntry &e)
{
    assert(e.mem_obj);
    const int32_t index = e.mem_obj->memCache.index;
    assert(index >= 0);
    assert(map);

    debugs(20, 5, "mem-cached all " << e.mem_obj->memCache.offset << " bytes of " << e);

    e.mem_obj->memCache.index = -1;
    e.mem_obj->memCache.io = MemObject::ioDone;
    map->closeForWriting(index, false);

    CollapsedForwarding::Broadcast(e); // before we close our transient entry!
    Store::Root().transientsCompleteWriting(e);
}