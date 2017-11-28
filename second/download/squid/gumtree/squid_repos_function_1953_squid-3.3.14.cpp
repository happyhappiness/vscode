void
StoreHashIndex::reference(StoreEntry &e)
{
    e.store()->reference(e);
}