IpAddress *
client_entry(IpAddress *current)
{
    ClientInfo *c = NULL;
    char key[MAX_IPSTRLEN];

    if (current) {
        current->NtoA(key,MAX_IPSTRLEN);
        hash_first(client_table);
        while ((c = (ClientInfo *) hash_next(client_table))) {
            if (!strcmp(key, hashKeyStr(&c->hash)))
                break;
        }

        c = (ClientInfo *) hash_next(client_table);
    } else {
        hash_first(client_table);
        c = (ClientInfo *) hash_next(client_table);
    }

    hash_last(client_table);

    if (c)
        return (&c->addr);
    else
        return (NULL);

}