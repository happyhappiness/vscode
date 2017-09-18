ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, cmd->server,
                 "Digest: Set shmem-size: %ld, num-buckets: %ld", shmem_size,
                 num_buckets);