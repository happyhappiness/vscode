void
MemStore::disconnect(StoreEntry &e)
{
    assert(e.mem_obj);
    MemObject &mem_obj = *e.mem_obj;
    if (mem_obj.memCache.index >= 0) {
        if (mem_obj.memCache.io == MemObject::ioWriting) {
            map->abortWriting(mem_obj.memCache.index);
            mem_obj.memCache.index = -1;
            mem_obj.memCache.io = MemObject::ioDone;
            Store::Root().transientsAbandon(e); // broadcasts after the change
        } else {
            assert(mem_obj.memCache.io == MemObject::ioReading);
            map->closeForReading(mem_obj.memCache.index);
            mem_obj.memCache.index = -1;
            mem_obj.memCache.io = MemObject::ioDone;
        }
    }
}