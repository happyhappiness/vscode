static void
fqdncacheFreeEntry(void *data)
{
    fqdncache_entry *f = (fqdncache_entry *)data;
    delete f;
}