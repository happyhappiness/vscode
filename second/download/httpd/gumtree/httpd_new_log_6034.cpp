ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, diary->entries->pool,
                  "push_diary_append: %"APR_UINT64_T_HEX_FMT, ne->hash);