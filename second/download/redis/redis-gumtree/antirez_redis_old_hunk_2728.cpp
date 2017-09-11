
    /* Server */
    if (allsections || defsections || !strcasecmp(section,"server")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
            "redis_git_sha1:%s\r\n"
            "redis_git_dirty:%d\r\n"
            "arch_bits:%d\r\n"
            "multiplexing_api:%s\r\n"
            "gcc_version:%d.%d.%d\r\n"
