line = sdscatprintf(sdsempty(),"%s %s %llu %llu %ld",
                option,
                getClientLimitClassName(j),
                server.client_obuf_limits[j].hard_limit_bytes,
                server.client_obuf_limits[j].soft_limit_bytes,
                (long) server.client_obuf_limits[j].soft_limit_seconds);