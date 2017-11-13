ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "Digest: Set shmem-size: %" APR_SIZE_T_FMT ", num-buckets: %ld", 
                 shmem_size, num_buckets);