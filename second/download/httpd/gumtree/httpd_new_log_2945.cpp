ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "finished insert, subcache: idx_pos/idx_used=%d/%d, "
                 "data_pos/data_used=%d/%d",
                 subcache->idx_pos, subcache->idx_used,
                 subcache->data_pos, subcache->data_used);