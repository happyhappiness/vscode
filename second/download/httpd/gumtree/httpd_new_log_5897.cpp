ap_log_error(APLOG_MARK, APLOG_DEBUG , 0, s, APLOGNO(02639)
                 "Using SO_REUSEPORT: %s (%d)",
                 ap_have_so_reuseport ? "yes" : "no",
                 ap_num_listen_buckets);