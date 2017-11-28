int
Transients::readers(const StoreEntry &e) const
{
    if (e.mem_obj && e.mem_obj->xitTable.index >= 0) {
        assert(map);
        return map->peekAtEntry(e.mem_obj->xitTable.index).lock.readers;
    }
    return 0;
}