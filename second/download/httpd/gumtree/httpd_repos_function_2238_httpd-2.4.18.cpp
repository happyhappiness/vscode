int h2_util_has_eos(apr_bucket_brigade *bb, apr_off_t len)
{
    apr_bucket *b, *end;
    
    apr_status_t status = last_not_included(bb, len, 0, 0, &end);
    if (status != APR_SUCCESS) {
        return status;
    }
    
    for (b = APR_BRIGADE_FIRST(bb);
         b != APR_BRIGADE_SENTINEL(bb) && b != end;
         b = APR_BUCKET_NEXT(b))
    {
        if (APR_BUCKET_IS_EOS(b)) {
            return 1;
        }
    }
    return 0;
}