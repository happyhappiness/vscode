int
Store::Controller::transientReaders(const StoreEntry &e) const
{
    return (transients && e.mem_obj && e.mem_obj->xitTable.index >= 0) ?
           transients->readers(e) : 0;
}