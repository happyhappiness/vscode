ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "idx->s_id2=%u, id[1]=%u, offset=%u",
                idx->s_id2, id[1], shmcb_get_safe_uint(&(idx->offset)));