static apr_status_t have_lf_or_eos(apr_bucket_brigade *bb)
{
    apr_bucket *b = APR_BRIGADE_LAST(bb);

    for ( ; b != APR_BRIGADE_SENTINEL(bb) ; b = APR_BUCKET_PREV(b) ) {
    	const char *str;
    	apr_size_t len;
    	apr_status_t rv;

        if (APR_BUCKET_IS_EOS(b))
            return APR_SUCCESS;

        if (APR_BUCKET_IS_METADATA(b))
            continue;

        rv = apr_bucket_read(b, &str, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS)
            return rv;

        if (len == 0)
            continue;

        if (str[len-1] == APR_ASCII_LF)
            return APR_SUCCESS;
    }
    return APR_INCOMPLETE;
}