int h2_util_bb_has_data(apr_bucket_brigade *bb)
{
    apr_bucket *b;
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        if (!APR_BUCKET_IS_METADATA(b)) {
            return 1;
        }
    }
    return 0;
}