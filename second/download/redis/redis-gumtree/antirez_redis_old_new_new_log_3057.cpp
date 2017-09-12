info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
            "redis_git_sha1:%s\r\n"
            "redis_git_dirty:%d\r\n"
            "arch_bits:%s\r\n"
            "multiplexing_api:%s\r\n"
            "process_id:%ld\r\n"
            "tcp_port:%d\r\n"
            "uptime_in_seconds:%ld\r\n"
            "uptime_in_days:%ld\r\n"
            "lru_clock:%ld\r\n",
            REDIS_VERSION,
            redisGitSHA1(),
            strtol(redisGitDirty(),NULL,10) > 0,
            (sizeof(long) == 8) ? "64" : "32",
            aeGetApiName(),
            (long) getpid(),
            server.port,
            uptime,
            uptime/(3600*24),
            (unsigned long) server.lruclock);