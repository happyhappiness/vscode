static idns_query *
idnsFindQuery(unsigned short id)
{
    dlink_node *n;
    idns_query *q;

    for (n = lru_list.tail; n; n = n->prev) {
        q = (idns_query*)n->data;

        if (q->query_id == id)
            return q;
    }

    return NULL;
}