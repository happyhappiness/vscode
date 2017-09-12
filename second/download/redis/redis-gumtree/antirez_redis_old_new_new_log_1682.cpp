line = sdscatprintf(sdsempty(),
            "sentinel leader-epoch %s %llu",
            master->name, (unsigned long long) master->leader_epoch);