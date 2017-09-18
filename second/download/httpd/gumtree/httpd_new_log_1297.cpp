ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "MCacheMaxStreamingBuffer must be greater than or equal to MCacheMinObjectSize. "
                     "Resetting MCacheMaxStreamingBuffer to MCacheMinObjectSize.");