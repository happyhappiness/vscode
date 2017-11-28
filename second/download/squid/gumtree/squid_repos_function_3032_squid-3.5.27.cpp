void
StoreEntry::destroyMemObject()
{
    debugs(20, 3, HERE << "destroyMemObject " << mem_obj);

    if (MemObject *mem = mem_obj) {
        // Store::Root() is FATALly missing during shutdown
        if (mem->xitTable.index >= 0 && !shutting_down)
            Store::Root().transientsDisconnect(*mem);
        if (mem->memCache.index >= 0 && !shutting_down)
            Store::Root().memoryDisconnect(*this);

        setMemStatus(NOT_IN_MEMORY);
        mem_obj = NULL;
        delete mem;
    }
}