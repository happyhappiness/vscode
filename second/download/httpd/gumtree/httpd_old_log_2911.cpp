ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "we now have %u sessions",
                     shmcb_get_safe_uint(queue->pos_count));