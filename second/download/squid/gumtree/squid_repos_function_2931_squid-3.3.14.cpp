int
clientdbEstablished(const Ip::Address &addr, int delta)
{
    char key[MAX_IPSTRLEN];
    ClientInfo *c;

    if (!Config.onoff.client_db)
        return 0;

    addr.NtoA(key,MAX_IPSTRLEN);

    c = (ClientInfo *) hash_lookup(client_table, key);

    if (c == NULL) {
        c = clientdbAdd(addr);
    }

    if (c == NULL)
        debug_trap("clientdbUpdate: Failed to add entry");

    c->n_established += delta;

    return c->n_established;
}