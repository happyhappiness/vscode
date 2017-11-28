static int
external_acl_entry_expired(external_acl * def, external_acl_entry * entry)
{
    if (entry->date + (entry->result == 1 ? def->ttl : def->negative_ttl) < squid_curtime)
        return 1;
    else
        return 0;
}