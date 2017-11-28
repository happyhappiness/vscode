static void
ipcacheAddEntry(ipcache_entry * i)
{
    hash_link *e = (hash_link *)hash_lookup(ip_table, i->hash.key);

    if (NULL != e) {
        /* avoid colission */
        ipcache_entry *q = (ipcache_entry *) e;
        ipcacheRelease(q);
    }

    hash_join(ip_table, &i->hash);
    dlinkAdd(i, &i->lru, &lru_list);
    i->lastref = squid_curtime;
}