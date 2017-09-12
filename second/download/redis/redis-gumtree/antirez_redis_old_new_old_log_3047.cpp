info = sdscatprintf(info,
                "cache_max_memory:%llu\r\n"
                "cache_blocked_clients:%lu\r\n"
                ,(unsigned long long) server.cache_max_memory,
                (unsigned long) server.cache_blocked_clients
            );