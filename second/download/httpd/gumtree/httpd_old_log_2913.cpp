ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "about to scroll %u sessions from %u",
                         loop, shmcb_get_safe_uint(queue->pos_count));