static void
external_acl_cache_touch(external_acl * def, external_acl_entry * entry)
{
    dlinkDelete(&entry->lru, &def->lru_list);
    dlinkAdd(entry, &entry->lru, &def->lru_list);
}