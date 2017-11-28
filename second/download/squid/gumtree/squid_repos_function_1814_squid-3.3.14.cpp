static int
external_acl_grace_expired(external_acl * def, external_acl_entry * entry)
{
    if (def->cache_size <= 0)
        return 1;

    int ttl;
    ttl = entry->result == 1 ? def->ttl : def->negative_ttl;
    ttl = (ttl * (100 - def->grace)) / 100;

    if (entry->date + ttl <= squid_curtime)
        return 1;
    else
        return 0;
}