static void
ipcacheFreeEntry(void *data)
{
    ipcache_entry *i = (ipcache_entry *)data;
    safe_free(i->addrs.in_addrs);
    safe_free(i->addrs.bad_mask);
    safe_free(i->hash.key);
    safe_free(i->error_message);
    memFree(i, MEM_IPCACHE_ENTRY);
}