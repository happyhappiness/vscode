static int indexing_comp(void *a, void *b)
{
    void *ac = (void *) (((apr_skiplist *) a)->compare);
    void *bc = (void *) (((apr_skiplist *) b)->compare);
    return ((ac < bc) ? -1 : ((ac > bc) ? 1 : 0));
}