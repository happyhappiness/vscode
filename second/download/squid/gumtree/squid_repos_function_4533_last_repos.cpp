void
Store::Disks::reference(StoreEntry &e)
{
    e.disk().reference(e);
}