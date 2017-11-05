ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "entering shmcb_insert_encoded_session, "
                 "*queue->pos_count = %u",
                 shmcb_get_safe_uint(queue->pos_count));