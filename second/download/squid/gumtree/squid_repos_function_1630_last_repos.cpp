void ClientDelayPool::dump(StoreEntry * entry, unsigned int poolNumberMinusOne) const
{
    LOCAL_ARRAY(char, nom, 32);
    snprintf(nom, 32, "client_delay_access %d", poolNumberMinusOne + 1);
    dump_acl_access(entry, nom, access);
    storeAppendPrintf(entry, "client_delay_parameters %d %d %" PRId64 "\n", poolNumberMinusOne + 1, rate,highwatermark);
    storeAppendPrintf(entry, "\n");
}