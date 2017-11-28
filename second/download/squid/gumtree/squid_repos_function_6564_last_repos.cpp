static void
netdbHostDelete(const net_db_name * x)
{
    assert(x != NULL);
    assert(x->net_db_entry != NULL);

    netdbEntry *n = x->net_db_entry;
    -- n->link_count;

    for (auto **X = &n->hosts; *X; X = &(*X)->next) {
        if (*X == x) {
            *X = x->next;
            break;
        }
    }

    hash_remove_link(host_table, (hash_link *) x);
    delete x;
}