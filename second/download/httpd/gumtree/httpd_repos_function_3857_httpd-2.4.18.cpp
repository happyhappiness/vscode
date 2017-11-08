static void remove_empty_buckets(apr_bucket_brigade *bb)
{
    apr_bucket *bucket;
    while (((bucket = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) &&
           (APR_BUCKET_IS_METADATA(bucket) || (bucket->length == 0))) {
        apr_bucket_delete(bucket);
    }
}