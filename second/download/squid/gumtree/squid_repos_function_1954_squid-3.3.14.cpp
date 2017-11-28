bool
StoreHashIndex::dereference(StoreEntry &e, bool wantsLocalMemory)
{
    return e.store()->dereference(e, wantsLocalMemory);
}