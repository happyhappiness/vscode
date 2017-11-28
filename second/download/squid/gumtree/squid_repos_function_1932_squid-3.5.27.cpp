static ExternalACLEntryPointer
external_acl_cache_add(external_acl * def, const char *key, ExternalACLEntryData const & data)
{
    ExternalACLEntryPointer entry;

    if (!def->maybeCacheable(data.result)) {
        debugs(82,6, HERE);
        if (data.result == ACCESS_DUNNO) {
            const ExternalACLEntryPointer oldentry = static_cast<ExternalACLEntry *>(hash_lookup(def->cache, key));
            if (oldentry != NULL)
                external_acl_cache_delete(def, oldentry);
        }
        entry = new ExternalACLEntry;
        entry->key = xstrdup(key);
        entry->update(data);
        entry->def = def;
        return entry;
    }

    entry = static_cast<ExternalACLEntry *>(hash_lookup(def->cache, key));
    debugs(82, 2, "external_acl_cache_add: Adding '" << key << "' = " << data.result);

    if (entry != NULL) {
        debugs(82, 3, "updating existing entry");
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