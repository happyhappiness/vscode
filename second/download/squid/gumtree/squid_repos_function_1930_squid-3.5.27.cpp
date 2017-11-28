static int
external_acl_entry_expired(external_acl * def, const ExternalACLEntryPointer &entry)
{
    if (def->cache_size <= 0 || entry->result == ACCESS_DUNNO)
        return 1;

    if (entry->date + (entry->result == ACCESS_ALLOWED ? def->ttl : def->negative_ttl) < squid_curtime)
        return 1;
    else
        return 0;
}