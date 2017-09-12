    
    info = sdscatprintf(sdsempty(),
        "redis_version:%s\r\n"
        "uptime_in_seconds:%d\r\n"
        "uptime_in_days:%d\r\n"
        "connected_clients:%d\r\n"
        "connected_slaves:%d\r\n"
        "used_memory:%zu\r\n"
