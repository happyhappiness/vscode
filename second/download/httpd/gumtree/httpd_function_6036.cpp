static apr_status_t gset_encode_next(gset_encoder *encoder, apr_uint64_t pval)
{
    apr_uint64_t delta, flex_bits;
    apr_status_t status = APR_SUCCESS;
    int i;
    
    delta = pval - encoder->last;
    encoder->last = pval;
    flex_bits = (delta >> encoder->fixed_bits);
    /* Intentional no APLOGNO */
    ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, encoder->pool,
                  "h2_push_diary_enc: val=%"APR_UINT64_T_HEX_FMT", delta=%"
                  APR_UINT64_T_HEX_FMT" flex_bits=%"APR_UINT64_T_FMT", "
                  ", fixed_bits=%d, fixed_val=%"APR_UINT64_T_HEX_FMT, 
                  pval, delta, flex_bits, encoder->fixed_bits, delta&encoder->fixed_mask);
    for (; flex_bits != 0; --flex_bits) {
        status = gset_encode_bit(encoder, 1);
        if (status != APR_SUCCESS) {
            return status;
        }
    }
    status = gset_encode_bit(encoder, 0);
    if (status != APR_SUCCESS) {
        return status;
    }

    for (i = encoder->fixed_bits-1; i >= 0; --i) {
        status = gset_encode_bit(encoder, (delta >> i) & 1);
        if (status != APR_SUCCESS) {
            return status;
        }
    }
    return APR_SUCCESS;
}