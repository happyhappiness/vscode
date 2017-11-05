ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, decoder->pool,
                  "h2_push_diary_digest_dec: val=%"APR_UINT64_T_HEX_FMT", delta=%"
                  APR_UINT64_T_HEX_FMT", flex=%d, fixed=%"APR_UINT64_T_HEX_FMT, 
                  *phash, delta, (int)flex, fixed);