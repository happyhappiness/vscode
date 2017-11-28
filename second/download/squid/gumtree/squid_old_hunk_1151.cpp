    debugs(20, 3, HERE << "mem-loading failed; freeing " << index);
    map->freeEntry(index); // do not let others into the same trap
    return NULL;
}

void
MemStore::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    // XXX: not needed but Store parent forces us to implement this
    fatal("MemStore::get(key,callback,data) should not be called");
}

bool
MemStore::anchorCollapsed(StoreEntry &collapsed, bool &inSync)
{
    if (!map)
