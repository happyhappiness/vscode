ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, pool,
                  "h2_push_diary_digest_set: diary now with %d entries, mask_bits=%d", 
                  (int)diary->entries->nelts, diary->mask_bits);