static void skiplisti_destroy(void *vsl)
{
    apr_skiplist_destroy((apr_skiplist *) vsl, NULL);
    apr_skiplist_free((apr_skiplist *) vsl, vsl);
}