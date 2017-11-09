static void h2_blist_cleanup(h2_blist *bl)
{
    apr_bucket *e;

    while (!H2_BLIST_EMPTY(bl)) {
        e = H2_BLIST_FIRST(bl);
        apr_bucket_delete(e);
    }
}