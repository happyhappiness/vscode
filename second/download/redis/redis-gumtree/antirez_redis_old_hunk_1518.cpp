    if (n != myself && error_code) *error_code = REDIS_CLUSTER_REDIR_MOVED;
    return n;
}
