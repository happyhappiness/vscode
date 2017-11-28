void
linklistPush(link_list ** L, void *p)
{
    link_list *l = (link_list *)memAllocate(MEM_LINK_LIST);
    l->next = NULL;
    l->ptr = p;

    while (*L)
        L = &(*L)->next;

    *L = l;
}