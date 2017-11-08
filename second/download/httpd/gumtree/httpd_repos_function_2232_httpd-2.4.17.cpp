apr_status_t h2_util_bb_avail(apr_bucket_brigade *bb, 
                              apr_size_t *plen, int *peos)
{
    apr_status_t status;
    apr_off_t blen = 0;

    /* test read to determine available length */
    status = apr_brigade_length(bb, 1, &blen);
    if (status != APR_SUCCESS) {
        return status;
    }
    else if (blen == 0) {
        /* empty brigade, does it have an EOS bucket somwhere? */
        *plen = 0;
        *peos = h2_util_has_eos(bb, 0);
    }
    else if (blen > 0) {
        /* data in the brigade, limit the length returned. Check for EOS
         * bucket only if we indicate data. This is required since plen == 0
         * means "the whole brigade" for h2_util_hash_eos()
         */
        if (blen < (apr_off_t)*plen) {
            *plen = blen;
        }
        *peos = (*plen > 0)? h2_util_has_eos(bb, *plen) : 0;
    }
    else if (blen < 0) {
        /* famous SHOULD NOT HAPPEN, sinc we told apr_brigade_length to readall
         */
        *plen = 0;
        *peos = h2_util_has_eos(bb, 0);
        return APR_EINVAL;
    }
    return APR_SUCCESS;
}