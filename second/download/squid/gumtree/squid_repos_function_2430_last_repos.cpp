ClientInfo * clientdbGetInfo(const Ip::Address &addr)
{
    char key[MAX_IPSTRLEN];
    ClientInfo *c;

    if (!Config.onoff.client_db)
        return NULL;

    addr.toStr(key,MAX_IPSTRLEN);

    c = (ClientInfo *) hash_lookup(client_table, key);
    if (c==NULL) {
        debugs(77, DBG_IMPORTANT,"Client db does not contain information for given IP address "<<(const char*)key);
        return NULL;
    }
    return c;
}