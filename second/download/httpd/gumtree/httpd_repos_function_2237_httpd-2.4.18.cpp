int h2_util_has_flush_or_eos(apr_bucket_brigade *bb) {
    apr_bucket *b;
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        if (APR_BUCKET_IS_EOS(b) || APR_BUCKET_IS_FLUSH(b)) {
            return 1;
        }
    }
    return 0;
}