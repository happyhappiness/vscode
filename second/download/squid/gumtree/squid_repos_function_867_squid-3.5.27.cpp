void
Transients::abandon(const StoreEntry &e)
{
    assert(e.mem_obj && map);
    map->freeEntry(e.mem_obj->xitTable.index); // just marks the locked entry
    CollapsedForwarding::Broadcast(e);
    // We do not unlock the entry now because the problem is most likely with
    // the server resource rather than a specific cache writer, so we want to
    // prevent other readers from collapsing requests for that resource.
}