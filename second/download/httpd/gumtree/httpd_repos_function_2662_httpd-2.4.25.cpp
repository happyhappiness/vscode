static void r_purge_sent(h2_bucket_beam *beam)
{
    apr_bucket *b;
    /* delete all sender buckets in purge brigade, needs to be called
     * from sender thread only */
    while (!H2_BLIST_EMPTY(&beam->purge_list)) {
        b = H2_BLIST_FIRST(&beam->purge_list);
        apr_bucket_delete(b);
    }
}