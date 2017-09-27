ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, pool,
                      "h2_push_diary_digest_get: golomb compressed hashes, %d bytes",
                      (int)encoder.offset + 1);