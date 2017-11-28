static int
external_acl_grace_expired(external_acl * def, const ExternalACLEntryPointer &entry)
{
    if (def->cache_size <= 0 || entry->result == ACCESS_DUNNO)
        return 1;

    int ttl;
    ttl = entry->result.allowed() ? def->ttl : def->negative_ttl;
    ttl = (ttl * (100 - def->grace)) / 100;

    if (entry->date + ttl <= squid_curtime)
        return 1;
    else
        return 0;
}