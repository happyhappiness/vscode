ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s,
                         "MCacheMaxStreamingBuffer must be less than or equal to MCacheMaxObjectSize. "
                         "Resetting MCacheMaxStreamingBuffer to MCacheMaxObjectSize.");