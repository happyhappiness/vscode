ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, pool,
                  "h2_push_diary_digest_get: %d entries, N=%d, log2n=%d, "
                  "mask_bits=%d, enc.mask_bits=%d, delta_bits=%d, enc.log2p=%d, authority=%s", 
                  (int)nelts, (int)N, (int)log2n, diary->mask_bits, 
                  (int)encoder.mask_bits, (int)encoder.delta_bits, 
                  (int)encoder.log2p, authority);