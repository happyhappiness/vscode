static external_acl_entry *
external_acl_cache_add(external_acl * def, const char *key, ExternalACLEntryData const & data)
{
    ExternalACLEntry *entry;

    // do not bother caching this result if TTL is going to expire it immediately
    if (def->cache_size <= 0 || (def->ttl <= 0 && data.result == 1) || (def->negative_ttl <= 0 && data.result != 1)) {
        debugs(82,6, HERE);
        entry = new ExternalACLEntry;
        entry->key = xstrdup(key);
        entry->update(data);
        entry->def = def;
        return entry;
    }

    entry = static_cast<ExternalACLEntry *>(hash_lookup(def->cache, key));
    debugs(82, 2, "external_acl_cache_add: Adding '" << key << "' = " << data.result);

    if (entry) {
        debugs(82, 3, "ExternalACLEntry::update: updating existing entry");
        entry->update(data);
        external_acl_cache_touch(def, entry);

        return entry;
    }

    entry = new ExternalACLEntry;
    entry->key = xstrdup(key);
    entry->update(data);

    def->add(entry);

    return entry;
}