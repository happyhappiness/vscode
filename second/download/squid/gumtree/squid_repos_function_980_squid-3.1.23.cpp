void
dlinkAdd(void *data, dlink_node * m, dlink_list * list)
{
    m->data = data;
    m->prev = NULL;
    m->next = list->head;

    if (list->head)
        list->head->prev = m;

    list->head = m;

    if (list->tail == NULL)
        list->tail = m;
}