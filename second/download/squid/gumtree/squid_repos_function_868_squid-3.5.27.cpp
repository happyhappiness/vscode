bool
Transients::abandoned(const StoreEntry &e) const
{
    assert(e.mem_obj);
    return abandonedAt(e.mem_obj->xitTable.index);
}