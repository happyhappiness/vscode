apr_off_t h2_brigade_mem_size(apr_bucket_brigade *bb)
{
    apr_bucket *b;
    apr_off_t total = 0;

    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb);
         b = APR_BUCKET_NEXT(b))
    {
        total += sizeof(*b);
        if (b->length > 0) {
            if (APR_BUCKET_IS_HEAP(b)
                || APR_BUCKET_IS_POOL(b)) {
                total += b->length;
            }
        }
    }
    return total;
}