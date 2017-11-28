void *
linklistShift(link_list ** L)
{
    void *p;
    link_list *l;

    if (NULL == *L)
        return NULL;

    l = *L;

    p = l->ptr;

    *L = (*L)->next;

    memFree(l, MEM_LINK_LIST);

    return p;
}