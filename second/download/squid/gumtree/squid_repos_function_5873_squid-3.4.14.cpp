static void
netdbHostDelete(const net_db_name * x)
{
    netdbEntry *n;
    net_db_name **X;
    assert(x != NULL);
    assert(x->net_db_entry != NULL);
    n = x->net_db_entry;
    -- n->link_count;

    for (X = &n->hosts; *X; X = &(*X)->next) {
        if (*X == x) {
            *X = x->next;
            break;
        }
    }

    hash_remove_link(host_table, (hash_link *) x);
    xfree(x->hash.key);
    memFree((void *) x, MEM_NET_DB_NAME);
}