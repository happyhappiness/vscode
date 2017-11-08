static int indexing_compk(void *ac, void *b)
{
    void *bc = (void *) (((apr_skiplist *) b)->compare);
    return ((ac < bc) ? -1 : ((ac > bc) ? 1 : 0));
}