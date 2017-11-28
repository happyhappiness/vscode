static
void
fvdbFreeEntry(void *data)
{
    fvdb_entry *fv = static_cast <fvdb_entry *>(data);
    xfree(fv->hash.key);
    xfree(fv);
}