ap_log_perror(APLOG_MARK, APLOG_INFO, 0, p, APLOGNO(02819)
                              "Using %i listeners bucket(s) based on %i "
                              "online CPU cores and a ratio of %i",
                              *num_buckets, num_online_cores,
                              ap_listencbratio);