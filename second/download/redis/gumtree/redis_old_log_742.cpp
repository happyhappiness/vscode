key = sdscatprintf(sdsempty(),
        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
        ip,port);