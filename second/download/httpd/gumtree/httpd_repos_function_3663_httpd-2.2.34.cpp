static void skiplisti_destroy(void *vsl)
{
    apr_skiplist_destroy(vsl, NULL);
}