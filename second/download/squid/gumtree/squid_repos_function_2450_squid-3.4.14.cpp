static void
ipcacheRelease(ipcache_entry * i, bool dofree)
{
    if (!i) {
        debugs(14, DBG_CRITICAL, "ipcacheRelease: Releasing entry with i=<NULL>");
        return;
    }

    if (!i || !i->hash.key) {
        debugs(14, DBG_CRITICAL, "ipcacheRelease: Releasing entry without hash link!");
        return;
    }

    debugs(14, 3, "ipcacheRelease: Releasing entry for '" << (const char *) i->hash.key << "'");

    hash_remove_link(ip_table, (hash_link *) i);
    dlinkDelete(&i->lru, &lru_list);
    if (dofree)
        ipcacheFreeEntry(i);
}