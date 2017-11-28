void
hashFreeItems(hash_table * hid, HASHFREE * free_func)
{
    hash_link *l;
    hash_link **list;
    int i = 0;
    int j;
    list = xcalloc(hid->count, sizeof(hash_link *));
    hash_first(hid);
    while ((l = hash_next(hid)) && i < hid->count) {
        *(list + i) = l;
        i++;
    }
    for (j = 0; j < i; j++)
        free_func(*(list + j));
    xfree(list);
}