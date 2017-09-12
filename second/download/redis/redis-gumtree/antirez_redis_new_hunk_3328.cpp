            info = sdscatprintf(info,
                "cache_max_memory:%llu\r\n"
                "cache_blocked_clients:%lu\r\n"
                "cache_io_queue_len:%lu\r\n"
                "cache_io_jobs_new:%lu\r\n"
                "cache_io_jobs_processing:%lu\r\n"
                "cache_io_jobs_processed:%lu\r\n"
                "cache_io_ready_clients:%lu\r\n"
                ,(unsigned long long) server.cache_max_memory,
                (unsigned long) server.cache_blocked_clients,
                (unsigned long) listLength(server.cache_io_queue),
                (unsigned long) listLength(server.io_newjobs),
                (unsigned long) listLength(server.io_processing),
                (unsigned long) listLength(server.io_processed),
                (unsigned long) listLength(server.io_ready_clients)
            );
            unlockThreadedIO();
        }
