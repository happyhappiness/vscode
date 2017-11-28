int
compare_heap_keys(const void *a, const void *b)
{
    heap_node **an = (heap_node **) a;
    heap_node **bn = (heap_node **) b;
    float cmp = (*an)->key - (*bn)->key;
    if (cmp < 0)
        return -1;
    else
        return 1;
}