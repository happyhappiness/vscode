static void
external_acl_cache_delete(external_acl * def, external_acl_entry * entry)
{
    assert(def->cache_size > 0 && entry->def == def);
    hash_remove_link(def->cache, entry);
    dlinkDelete(&entry->lru, &def->lru_list);
    def->cache_entries -= 1;
    delete entry;
}