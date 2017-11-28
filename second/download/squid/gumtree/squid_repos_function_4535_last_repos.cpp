void
Store::Disks::updateHeaders(StoreEntry *e)
{
    Must(e);
    return e->disk().updateHeaders(e);
}