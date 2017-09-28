line = sdscatprintf(sdsempty(),
            "sentinel config-epoch %s %llu",
            master->name, (unsigned long long) master->config_epoch);