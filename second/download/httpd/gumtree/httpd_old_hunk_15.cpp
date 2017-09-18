    shmem_size  = size;
    num_buckets = (size - sizeof(*client_list)) /
                  (sizeof(client_entry*) + HASH_DEPTH * sizeof(client_entry));
    if (num_buckets == 0) {
        num_buckets = 1;
    }
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, 0, cmd->server,
                 "Digest: Set shmem-size: %ld, num-buckets: %ld", shmem_size,
                 num_buckets);

    return NULL;
}

