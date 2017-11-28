static void
external_acl_cache_touch(external_acl * def, external_acl_entry * entry)
{
    // this must not be done when nothing is being cached.
    if (def->cache_size <= 0 || (def->ttl <= 0 && entry->result == 1) || (def->negative_ttl <= 0 && entry->result != 1))
        return;

    dlinkDelete(&entry->lru, &def->lru_list);
    dlinkAdd(entry, &entry->lru, &def->lru_list);
}