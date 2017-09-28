    getrusage(RUSAGE_SELF, &self_ru);
    getrusage(RUSAGE_CHILDREN, &c_ru);
    getClientsMaxBuffers(&lol,&bib);

    /* Server */
    if (allsections || defsections || !strcasecmp(section,"server")) {
        struct utsname name;
        char *mode;

        if (server.sentinel_mode) mode = "sentinel";
        else mode = "standalone";
    
        if (sections++) info = sdscat(info,"\r\n");
        uname(&name);
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
            "redis_git_sha1:%s\r\n"
            "redis_git_dirty:%d\r\n"
            "redis_build_id:%llx\r\n"
