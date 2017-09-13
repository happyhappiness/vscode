info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "redis_git_sha1:%s\r\n"
        "redis_git_dirty:%d\r\n"
        "arch_bits:%s\r\n"
        "multiplexing_api:%s\r\n"
        "process_id:%ld\r\n";