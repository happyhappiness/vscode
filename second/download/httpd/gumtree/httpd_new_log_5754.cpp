ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, p, APLOGNO(02820)
                              "ListenCoresBucketsRatio ignored without "
                              "SO_REUSEPORT and _SC_NPROCESSORS_ONLN "
                              "support: using a single listeners bucket");