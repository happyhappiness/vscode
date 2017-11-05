ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, pool,
                  "h2_push_diary_digest_set: N=%d, log2n=%d, "
                  "diary->mask_bits=%d, dec.log2p=%d", 
                  (int)diary->N, (int)log2n, diary->mask_bits, 
                  (int)decoder.log2p);