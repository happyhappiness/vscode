static void
ipcacheLockEntry(ipcache_entry * i)
{
    if (i->locks++ == 0) {
        dlinkDelete(&i->lru, &lru_list);
        dlinkAdd(i, &i->lru, &lru_list);
    }
}