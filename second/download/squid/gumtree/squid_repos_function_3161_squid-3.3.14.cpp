static void
fqdncacheAddEntry(fqdncache_entry * f)
{
    hash_link *e = (hash_link *)hash_lookup(fqdn_table, f->hash.key);

    if (NULL != e) {
        /* avoid colission */
        fqdncache_entry *q = (fqdncache_entry *) e;
        fqdncacheRelease(q);
    }

    hash_join(fqdn_table, &f->hash);
    dlinkAdd(f, &f->lru, &lru_list);
    f->lastref = squid_curtime;
}