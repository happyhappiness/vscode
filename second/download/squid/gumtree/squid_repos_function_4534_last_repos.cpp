bool
Store::Disks::dereference(StoreEntry &e)
{
    return e.disk().dereference(e);
}