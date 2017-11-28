void
Transients::completeWriting(const StoreEntry &e)
{
    if (e.mem_obj && e.mem_obj->xitTable.index >= 0) {
        assert(e.mem_obj->xitTable.io == MemObject::ioWriting);
        // there will be no more updates from us after this, so we must prevent
        // future readers from joining
        map->freeEntry(e.mem_obj->xitTable.index); // just marks the locked entry
        map->closeForWriting(e.mem_obj->xitTable.index);
        e.mem_obj->xitTable.index = -1;
        e.mem_obj->xitTable.io = MemObject::ioDone;
    }
}