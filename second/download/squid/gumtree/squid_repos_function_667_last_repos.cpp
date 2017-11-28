void
dlinkDelete(dlink_node * m, dlink_list * list)
{
    if (m->next)
        m->next->prev = m->prev;

    if (m->prev)
        m->prev->next = m->next;

    if (m == list->head)
        list->head = m->next;

    if (m == list->tail)
        list->tail = m->prev;

    m->next = m->prev = NULL;
}