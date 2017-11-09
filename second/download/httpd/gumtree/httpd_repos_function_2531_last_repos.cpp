static h2_push_diary *diary_create(apr_pool_t *p, h2_push_digest_type dtype, 
                                   int N)
{
    h2_push_diary *diary = NULL;
    
    if (N > 0) {
        diary = apr_pcalloc(p, sizeof(*diary));
        
        diary->NMax        = ceil_power_of_2(N);
        diary->N           = diary->NMax;
        /* the mask we use in value comparison depends on where we got
         * the values from. If we calculate them ourselves, we can use
         * the full 64 bits.
         * If we set the diary via a compressed golomb set, we have less
         * relevant bits and need to use a smaller mask. */
        diary->mask_bits   = 64;
        /* grows by doubling, start with a power of 2 */
        diary->entries     = apr_array_make(p, 16, sizeof(h2_push_diary_entry));
        
        switch (dtype) {
#ifdef H2_OPENSSL
            case H2_PUSH_DIGEST_SHA256:
                diary->dtype       = H2_PUSH_DIGEST_SHA256;
                diary->dcalc       = calc_sha256_hash;
                break;
#endif /* ifdef H2_OPENSSL */
            default:
                diary->dtype       = H2_PUSH_DIGEST_APR_HASH;
                diary->dcalc       = calc_apr_hash;
                break;
        }
    }
    
    return diary;
}