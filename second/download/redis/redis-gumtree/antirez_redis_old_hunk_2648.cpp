    /* Server */
    if (allsections || defsections || !strcasecmp(section,"server")) {
        struct utsname name;

        if (sections++) info = sdscat(info,"\r\n");
        uname(&name);
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
            "redis_git_sha1:%s\r\n"
            "redis_git_dirty:%d\r\n"
            "os:%s %s %s\r\n"
            "arch_bits:%d\r\n"
            "multiplexing_api:%s\r\n"
