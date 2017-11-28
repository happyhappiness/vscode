static void
ipcacheAddEntry(ipcache_entry * i)
{
    hash_link *e = (hash_link *)hash_lookup(ip_table, i->hash.key);

#if DNS_CNAME
    /* INET6 : should NOT be adding this entry until all CNAME have been received. */
    assert(i->cname_wait == 0);
#endif

    if (NULL != e) {
        /* avoid colission */
        ipcache_entry *q = (ipcache_entry *) e;
#if DNS_CNAME
        if (q == i)  {
            /* can occur with Multiple-depth CNAME Recursion if parent returned early with additional */
            /* just need to drop from the hash without releasing actual memory */
            ipcacheRelease(q, false);
        } else
#endif
            ipcacheRelease(q);
    }

    hash_join(ip_table, &i->hash);
    dlinkAdd(i, &i->lru, &lru_list);
    i->lastref = squid_curtime;
}