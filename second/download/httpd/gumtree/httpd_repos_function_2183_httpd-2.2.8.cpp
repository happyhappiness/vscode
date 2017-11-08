static void brigade_move(apr_bucket_brigade *b, apr_bucket_brigade *a,
                         apr_bucket *e)
{
    apr_bucket *f;

    if (e != APR_BRIGADE_SENTINEL(b)) {
        f = APR_RING_LAST(&b->list);
        APR_RING_UNSPLICE(e, f, link);
        APR_RING_SPLICE_HEAD(&a->list, e, f, apr_bucket, link);
    }

    APR_BRIGADE_CHECK_CONSISTENCY(a);
    APR_BRIGADE_CHECK_CONSISTENCY(b);
}