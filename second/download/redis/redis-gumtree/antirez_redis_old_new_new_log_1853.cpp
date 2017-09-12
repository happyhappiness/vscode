line = sdscatprintf(sdsempty(),
                "sentinel down-after-milliseconds %s %ld",
                master->name, (long) master->down_after_period);