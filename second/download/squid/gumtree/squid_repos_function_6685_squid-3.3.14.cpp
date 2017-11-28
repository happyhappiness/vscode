void
hashFreeItems(hash_table * hid, HASHFREE * free_func)
{
    hash_link *l;
    int i = 0;
    hash_link **list = (hash_link **)xcalloc(hid->count, sizeof(hash_link *));
    hash_first(hid);
    while ((l = hash_next(hid)) && i < hid->count) {
        *(list + i) = l;
        ++i;
    }
    for (int j = 0; j < i; ++j)
        free_func(*(list + j));
    xfree(list);
}