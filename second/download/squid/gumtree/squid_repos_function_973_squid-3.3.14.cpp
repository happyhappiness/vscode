void
dlinkAddAfter(void *data, dlink_node * m, dlink_node * n, dlink_list * list)
{
    m->data = data;
    m->prev = n;
    m->next = n->next;

    if (n->next)
        n->next->prev = m;
    else {
        assert(list->tail == n);
        list->tail = m;
    }

    n->next = m;
}