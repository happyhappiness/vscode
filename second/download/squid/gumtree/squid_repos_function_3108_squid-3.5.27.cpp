void
StoreEntry::transientsAbandonmentCheck()
{
    if (mem_obj && !mem_obj->smpCollapsed && // this worker is responsible
            mem_obj->xitTable.index >= 0 && // other workers may be interested
            mem_obj->memCache.index < 0 && // rejected by the shared memory cache
            mem_obj->swapout.decision == MemObject::SwapOut::swImpossible) {
        debugs(20, 7, "cannot be shared: " << *this);
        if (!shutting_down) // Store::Root() is FATALly missing during shutdown
            Store::Root().transientsAbandon(*this);
    }
}