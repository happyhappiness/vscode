static void
ipcacheFreeEntry(void *data)
{
    ipcache_entry *i = (ipcache_entry *)data;
    delete i;
}