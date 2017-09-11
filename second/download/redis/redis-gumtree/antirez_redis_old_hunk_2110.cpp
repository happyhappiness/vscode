
    /* Server */
    if (allsections || defsections || !strcasecmp(section,"server")) {
        struct utsname name;
        char *mode;

        if (server.cluster_enabled) mode = "cluster";
        else if (server.sentinel_mode) mode = "sentinel";
        else mode = "standalone";
    
        if (sections++) info = sdscat(info,"\r\n");
        uname(&name);
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
