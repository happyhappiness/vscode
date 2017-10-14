ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, encoder->pool,
                  "h2_push_diary_enc: val=%"APR_UINT64_T_HEX_FMT", delta=%"
                  APR_UINT64_T_HEX_FMT" flex_bits=%"APR_UINT64_T_FMT", "
                  ", fixed_bits=%d, fixed_val=%"APR_UINT64_T_HEX_FMT, 
                  pval, delta, flex_bits, encoder->fixed_bits, delta&encoder->fixed_mask);